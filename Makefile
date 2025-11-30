MEENGI_DIR := meengi
MEENGI_BIN := $(MEENGI_DIR)/meengi

.PHONY: all meengi site clean clean-site clean-meengi

all: site

meengi:
	$(MAKE) -C $(MEENGI_DIR)

site: meengi
	./$(MEENGI_BIN)

clean-site:
	rm -f site/*.html

clean-meengi:
	$(MAKE) -C $(MEENGI_DIR) clean

clean: clean-site clean-meengi
