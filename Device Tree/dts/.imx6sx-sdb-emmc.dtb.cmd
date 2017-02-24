cmd_arch/arm/boot/dts/imx6sx-sdb-emmc.dtb := arm-linux-gnueabihf-gcc -E -Wp,-MD,arch/arm/boot/dts/.imx6sx-sdb-emmc.dtb.d.pre.tmp -nostdinc -I/home/walter/linux-toradex/arch/arm/boot/dts -I/home/walter/linux-toradex/arch/arm/boot/dts/include -I/home/walter/linux-toradex/drivers/of/testcase-data -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/boot/dts/.imx6sx-sdb-emmc.dtb.dts.tmp arch/arm/boot/dts/imx6sx-sdb-emmc.dts ; /home/walter/linux-toradex/scripts/dtc/dtc -O dtb -o arch/arm/boot/dts/imx6sx-sdb-emmc.dtb -b 0 -i arch/arm/boot/dts/  -d arch/arm/boot/dts/.imx6sx-sdb-emmc.dtb.d.dtc.tmp arch/arm/boot/dts/.imx6sx-sdb-emmc.dtb.dts.tmp ; cat arch/arm/boot/dts/.imx6sx-sdb-emmc.dtb.d.pre.tmp arch/arm/boot/dts/.imx6sx-sdb-emmc.dtb.d.dtc.tmp > arch/arm/boot/dts/.imx6sx-sdb-emmc.dtb.d

source_arch/arm/boot/dts/imx6sx-sdb-emmc.dtb := arch/arm/boot/dts/imx6sx-sdb-emmc.dts

deps_arch/arm/boot/dts/imx6sx-sdb-emmc.dtb := \
  arch/arm/boot/dts/imx6sx-sdb.dts \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/input/input.h \
  arch/arm/boot/dts/imx6sx.dtsi \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/clock/imx6sx-clock.h \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/gpio/gpio.h \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/interrupt-controller/arm-gic.h \
  /home/walter/linux-toradex/arch/arm/boot/dts/include/dt-bindings/interrupt-controller/irq.h \
  arch/arm/boot/dts/imx6sx-pinfunc.h \
  arch/arm/boot/dts/skeleton.dtsi \

arch/arm/boot/dts/imx6sx-sdb-emmc.dtb: $(deps_arch/arm/boot/dts/imx6sx-sdb-emmc.dtb)

$(deps_arch/arm/boot/dts/imx6sx-sdb-emmc.dtb):
