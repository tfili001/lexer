.PHONY: clean All

All:
	@echo "----------Building project:[ lexer - Debug ]----------"
	@"$(MAKE)" -f  "lexer.mk"
clean:
	@echo "----------Cleaning project:[ lexer - Debug ]----------"
	@"$(MAKE)" -f  "lexer.mk" clean
