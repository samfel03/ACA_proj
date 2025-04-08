<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="com.autoesl.autopilot.project" name="sparsefpgaimp" top="loop_uhat_sparse">
  <files>
    <file name="../../../CCE-C/library/mainsparse.cpp" sc="0" tb="1" cflags="-IC:/Research/CU-Spur-Sean/spurFPGA/CCE-C/library/include -IC:/Research/CU-Spur-Sean/spurFPGA/CCE-C/library/include -Wno-unknown-pragmas" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/call_rcond.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="sparsefpgaimp/loop_uhat_sparse.cpp" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/rtGetInf.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/rtGetNaN.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/rt_nonfinite.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/svd.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/xaxpy.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/xdotc.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/xnrm2.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/xrot.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/xrotg.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    <file name="../CCE-C/library/src/xswap.c" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
  </files>
  <solutions>
    <solution name="loop_uhat_sparse_imp" status="active"/>
  </solutions>
  <includePaths/>
  <libraryPaths/>
  <Simulation argv="">
    <SimFlow name="csim" ldflags="" clean="true" csimMode="2" lastCsimMode="2"/>
  </Simulation>
</project>
