ifdef DAY

.PHONY: $(DAY)

SAMPLES = $(DAY)/sample*.txt
INPUTS = $(DAY)/input*.txt

$(DAY): $(DAY)/main.js $(SAMPLES) $(INPUTS)
	@node $(DAY)/main.js $(SAMPLES) $(INPUTS)

endif
