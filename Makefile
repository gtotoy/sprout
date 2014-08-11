.PHONY: clean All

All:
	@echo "----------Building project:[ yellow_flower - Release ]----------"
	@cd "yellow_flower" && $(MAKE) -f  "yellow_flower.mk"
clean:
	@echo "----------Cleaning project:[ yellow_flower - Release ]----------"
	@cd "yellow_flower" && $(MAKE) -f  "yellow_flower.mk" clean
