ifdef DAY

.PHONY: $(DAY)

SAMPLES = $(DAY)/sample*.txt
INPUTS = $(DAY)/input*.txt

$(DAY): $(DAY)/main.py $(SAMPLES) $(INPUTS)
	@python3 $(DAY)/main.py $(SAMPLES) $(INPUTS)

endif
