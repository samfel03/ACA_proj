<project xmlns="com.autoesl.autopilot.project" name="VitisHLS" top="add" projectType="C/C++">
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <files xmlns="">
        <file name="VitisHLS/add.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="../nandtb.cpp" sc="0" tb="1" cflags="-IC:/Research/CU-Spur-Sean/spurFPGA/SoCNANDTest/VitisHLS/. -Wno-unknown-pragmas" csimflags="" blackbox="false"/>
        <file name="../nandtb.h" sc="0" tb="1" cflags="-Wno-unknown-pragmas" csimflags="" blackbox="false"/>
    </files>
    <solutions xmlns="">
        <solution name="solution_1" status="active"/>
    </solutions>
</project>

