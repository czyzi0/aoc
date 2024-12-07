ifdef DAY

.PHONY: $(DAY)

SAMPLES = $(DAY)/sample*.txt
INPUTS = $(DAY)/input*.txt

$(DAY): $(DAY)/main.lua $(SAMPLES) $(INPUTS)
	@lua $(DAY)/main.lua $(SAMPLES) $(INPUTS)

endif
