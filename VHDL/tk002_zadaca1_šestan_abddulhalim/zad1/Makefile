TOP_LEVEL = top_tb

VHDL_SOURCES = \
	top.vhd \
	top_tb.vhd

SIM_FLAGS = --vcd=$(TOP_LEVEL).vcd --stop-time=200ns

GTKWAVE_CONFIG = top.ini
GTKWAVE_SAVE = top.sav

all: wave

wave: run
	gtkwave $(TOP_LEVEL).vcd $(GTKWAVE_SAVE) $(GTKWAVE_CONFIG)

run: elaborate
	ghdl -r $(TOP_LEVEL) $(SIM_FLAGS)

elaborate: compile
	ghdl -e $(TOP_LEVEL)

compile:
	ghdl -a $(VHDL_SOURCES)

clean:
	rm -f work-obj93.cf $(TOP_LEVEL).vcd *.o $(GTKWAVE_SAVE) $(GTKWAVE_CONFIG)

setup:
	@echo "[gtkwave]" > $(GTKWAVE_CONFIG)
	@echo "theme=dark" >> $(GTKWAVE_CONFIG)
	@echo "zoom=0" >> $(GTKWAVE_CONFIG)
	@touch $(GTKWAVE_SAVE)
