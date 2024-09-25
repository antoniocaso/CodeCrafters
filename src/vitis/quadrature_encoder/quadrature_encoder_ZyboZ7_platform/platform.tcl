# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\consegna\vitis\quadrature_encoder\quadrature_encoder_ZyboZ7_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\consegna\vitis\quadrature_encoder\quadrature_encoder_ZyboZ7_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {quadrature_encoder_ZyboZ7_platform}\
-hw {C:\consegna\vivado\quadrature_encoder\design_1_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/consegna/vitis/quadrature_encoder}

platform write
platform generate -domains 
platform active {quadrature_encoder_ZyboZ7_platform}
bsp reload
platform generate
