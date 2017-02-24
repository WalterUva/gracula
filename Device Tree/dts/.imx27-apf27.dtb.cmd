cmd_arch/arm/boot/dts/imx27-apf27.dtb := arm-linux-gnueabihf-gcc -E -Wp,-MD,arch/arm/boot/dts/.imx27-apf27.dtb.d.pre.tmp -nostdinc -I/home/walter/linux-toradex/arch/arm/boot/dts -I/home/walter/linux-toradex/arch/arm/boot/dts/include -I/home/walter/linux-toradex/drivers/of/testcase-data -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/boot/dts/.imx27-apf27.dtb.dts.tmp arch/arm/boot/dts/imx27-apf27.dts ; /home/walter/linux-toradex/scripts/dtc/dtc -O dtb -o arch/arm/boot/dts/imx27-apf27.dtb -b 0 -i arch/arm/boot/dts/  -d arch/arm/boot/dts/.imx27-apf27.dtb.d.dtc.tmp arch/arm/boot/dts/.imx27-apf27.dtb.dts.tmp ; cat arch/arm/boot/dts/.imx27-apf27.dtb.d.pre.tmp arch/arm/boot/dts/.imx27-apf27.dtb.d.dtc.tmp > arch/arm/boot/dts/.imx27-apf27.dtb.d

source_arch/arm/boot/dts/imx27-apf27.dtb := arch/arm/boot/dts/imx27-apf27.dts

deps_arch/arm/boot/dts/imx27-apf27.dtb := \
  arch/arm/boot/dts/imx27.dtsi \
  arch/arm/boot/dts/skeleton.dtsi \

arch/arm/boot/dts/imx27-apf27.dtb: $(deps_arch/arm/boot/dts/imx27-apf27.dtb)

$(deps_arch/arm/boot/dts/imx27-apf27.dtb):
