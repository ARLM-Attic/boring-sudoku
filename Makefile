.PHONY: clean All

All:
	@echo "----------Building project:[ boringsudoku - Debug ]----------"
	@$(MAKE) -f  "boringsudoku.mk"
clean:
	@echo "----------Cleaning project:[ boringsudoku - Debug ]----------"
	@$(MAKE) -f  "boringsudoku.mk" clean
