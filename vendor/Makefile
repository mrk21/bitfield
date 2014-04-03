BANDIT_VERSION = v1.1.4

.PHONY: all
all: bandit

.PHONY: clean
clean:
	${RM} -r bandit

bandit:
	git clone https://github.com/joakimkarlsson/bandit.git $@
	cd $@ && git checkout ${BANDIT_VERSION}
