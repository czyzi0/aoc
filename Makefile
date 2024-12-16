Y := $(shell date +%Y)

ifdef D

.PHONY: $(Y)/$(D)

SAMPLES = $(Y)/$(D)/sample*.txt
INPUTS = $(Y)/$(D)/input*.txt

all: $(Y)/$(D)

2024/$(D): $(Y)/$(D)/main.lua $(SAMPLES) $(INPUTS)
	@lua $(Y)/$(D)/main.lua $(SAMPLES) $(INPUTS)

2023/$(D): $(Y)/$(D)/main.py $(SAMPLES) $(INPUTS)
	@python3 $(Y)/$(D)/main.py $(SAMPLES) $(INPUTS)

2022/$(D): $(Y)/$(D)/main.js $(SAMPLES) $(INPUTS)
	@node $(Y)/$(D)/main.js $(SAMPLES) $(INPUTS)

endif
