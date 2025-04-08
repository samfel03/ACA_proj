#include <stdio.h>
#include <xparameters.h>
#include "xdogain.h"
#include "xaxidma.h"

// IP config pointers and handlers
XDogain doGain;
XDogain_Config *doGain_cfg;
XAxiDma axiDMA;
XAxiDma_Config *axiDMA_cfg;

// DMA Addresses
#define MEM_BASE_ADDR 0x01000000
#define TX_BUFFER_BASE (MEM_BASE_ADDR + 0x00100000)
#define RX_BUFFER_BASE (MEM_BASE_ADDR + 0x00300000)

#define SIZE_ARR 1000
int inStreamData[SIZE_ARR];

void initPeripherals() {

    // Initialize dogain core
    printf("Initializing doGain\n");
    doGain_cfg = XDogain_LookupConfig(0);
    if (doGain_cfg) {
        int status = XDogain_CfgInitialize(&doGain, doGain_cfg);
        if (status != XST_SUCCESS) {
            printf("Error initializing doGain core\n");
        }
    }

    // Initialize AxiDMA core
    printf("Initializing AxiMA\n");
    axiDMA_cfg = XAxiDma_LookupConfig(0);
    if (axiDMA_cfg) {
        int status = XAxiDma_CfgInitialize(&axiDMA, axiDMA_cfg);
        if (status != XST_SUCCESS) {
            printf("Error initializing AxiDMA core\n");
        }
    }

    // Disable interrupts
    XAxiDma_IntrDisable(&axiDMA, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
    XAxiDma_IntrDisable(&axiDMA, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);
}

int main() {

    // Pointers to DMA TX/RX addresses
    int *m_dma_buffer_TX = (int*) TX_BUFFER_BASE;
    int *m_dma_buffer_RX = (int*) RX_BUFFER_BASE;

    initPeripherals();

    // Do the stream calculation
    for (int idx = 0; idx < SIZE_ARR; idx++) {
        inStreamData[idx] = idx;
    }

    // Set gain to 5 and start core
    while (true) {

        int gain;
        printf("Choose gain: ");
        scanf("%d", &gain);
        XDogain_Set_gain(&doGain, gain);
        XDogain_Start(&doGain);

        // Flush the cache of the buffers
        Xil_DCacheFlushRange((u32)inStreamData, SIZE_ARR*sizeof(int));
        Xil_DCacheFlushRange((u32)m_dma_buffer_RX, SIZE_ARR*sizeof(int));

        printf("Sending data to IP core slave\n");
        XAxiDma_SimpleTransfer(&axiDMA, (u32)inStreamData, SIZE_ARR*sizeof(int), XAXIDMA_DMA_TO_DEVICE);

        printf("Get data\n");
        XAxiDma_SimpleTransfer(&axiDMA, (u32)m_dma_buffer_RX, SIZE_ARR*sizeof(int), XAXIDMA_DEVICE_TO_DMA);
        while (XAxiDma_Busy(&axiDMA, XAXIDMA_DEVICE_TO_DMA));

        // Invalidate the cache to avoid reading garbage
        Xil_DCacheInvalidateRange((u32)m_dma_buffer_RX, SIZE_ARR*sizeof(int));

        while (!XDogain_IsDone(&doGain));
        printf("Calculation complete\n");

        // Display data
        for (int idx = 0; idx < SIZE_ARR; idx++) {
            printf("Recv[%d]=%d\n", idx, m_dma_buffer_RX[idx]);
        }
    }

    return 0;
}