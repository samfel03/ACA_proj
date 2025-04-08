#include <stdio.h>
#include <xparameters.h>
#include "src/xadd.h"
#include "src/xadd_hw.h"
//#include "C:\Research\CU-Spur-Sean\spurFPGA\SoCNANDTest\VitisEmbedded\platform\ps7_cortexa9_0\standalone_ps7_cortexa9_0\bsp\hw_artifacts\drivers\add_v2_0\src\xadd.h"
#include "platform.h"




int add(int a, int b) {
	return a + b;
}





int main()
{
    init_platform();

    int status;
    XAdd doAdd;
    XAdd_Config *doAdd_cfg;

    doAdd_cfg = XAdd_LookupConfig(0); //ERROR MAYBE
    if (!doAdd_cfg)  {
        printf("Error loading config for doAdd_cfg\n");
    }

    status = XAdd_CfgInitialize(&doAdd, doAdd_cfg);

    if (status != XST_SUCCESS) {
        printf("Error initializing for doAdd\n");
    }




//RUN ADDER ON SOFTWARE
    printf("Running Adder Algortihm (SW) model");
    int result;
    printf("Expected: ");
	result = add(1,1);
	printf("%d", result);
	result = add(1,2);
	printf("%d", result);
	result = add(2,1);
	printf("%d", result);
	result = add(1,0);
	printf("%d\n", result);




// RUN ADDER ON HARDWARE
    XAdd_Set_a(&doAdd, 1);
    XAdd_Set_b(&doAdd, 1);
    // Start IP core execution
    XAdd_Start(&doAdd);
    // Wait until execution is finished
    while(!XAdd_IsDone(&doAdd));

    int out = (int) XAdd_Get_return(&doAdd);

    printf("-----%d-----", out);


    return 0;

}
