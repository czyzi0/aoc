SHELL = /bin/bash


ifdef DAY

.PHONY: $(DAY)

SAMPLES = $(DAY)/sample*.txt
INPUTS = $(DAY)/input*.txt


$(DAY): .venv/bin/activate $(DAY)/main.py $(INPUTS)
	@source .venv/bin/activate && black $(DAY)/main.py 2> /dev/null
	@source .venv/bin/activate && pylint \
		--exit-zero \
		--score=n \
		--disable=missing-module-docstring,missing-class-docstring,missing-function-docstring \
		$(DAY)/main.py
	@source .venv/bin/activate && python3 $(DAY)/main.py $(SAMPLES) $(INPUTS)

endif


.venv/bin/activate:
	@echo -e "Creating virtualenv"
	@python3 -m venv .venv/ && source .venv/bin/activate && pip3 install -r requirements.txt
	@echo -e "DONE\n"
