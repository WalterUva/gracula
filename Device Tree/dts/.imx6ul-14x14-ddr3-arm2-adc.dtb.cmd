cmd_arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2-adc.dtb := arm-linux-gnueabihf-gcc -E -Wp,-MD,arch/arm/boot/dts/.imx6ul-14x14-ddr3-arm2-adc.dtb.d.pre.tmp -nostdinc -I/home/walter/linux-toradex/arch/arm/boot/dts -I/home/walter/linux-toradex/arch/arm/boot/dts/include -I/home/walter/linux-toradex/drivers/of/testcase-data -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/boot/dts/.imx6ul-14x14-ddr3-arm2-adc.dtb.dts.tmp arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2-adc.dts ; /home/walter/linux-toradex/scripts/dtc/dtc -O dtb -o arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2-adc.dtb -b 0 -i arch/arm/boot/dts/  -d arch/arm/boot/dts/.imx6ul-14x14-ddr3-arm2-adc.dtb.d.dtc.tmp arch/arm/boot/dts/.imx6ul-14x14-ddr3-arm2-adc.dtb.dts.tmp ; cat arch/arm/boot/dts/.imx6ul-14x14-ddr3-arm2-adc.dtb.d.pre.tmp arch/arm/boot/dts/.imx6ul-14x14-ddr3-arm2-adc.dtb.d.dtc.tmp > arch/arm/boot/dts/.imx6ul-14x14-ddr3-arm2-adc.dtb.d

source_arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2-adc.dtb := arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2-adc.dts

deps_arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2-adc.dtb := \
  arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2.dts \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/input/input.h \
  arch/arm/boot/dts/imx6ul.dtsi \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/clock/imx6ul-clock.h \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/gpio/gpio.h \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/interrupt-controller/arm-gic.h \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/interrupt-controller/irq.h \
  arch/arm/boot/dts/imx6ul-pinfunc.h \
  arch/arm/boot/dts/skeleton.dtsi \

arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2-adc.dtb: $(deps_arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2-adc.dtb)

$(deps_arch/arm/boot/dts/imx6ul-14x14-ddr3-arm2-adc.dtb):
