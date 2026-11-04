LATEX = pdflatex
FLAGS = -interaction=nonstopmode -halt-on-error

DEPS = main.tex estilo.tex \
       $(wildcard secciones/*.tex) \
       $(wildcard secciones/strings/*.tex) \
       $(wildcard secciones/juegos/*.tex) \
       $(wildcard secciones/flujo/*.tex) \
       $(wildcard secciones/mate/*.tex) \
       $(wildcard codigo/*.cpp)

all: main.pdf

main.pdf: $(DEPS)
	$(LATEX) $(FLAGS) main.tex
	$(LATEX) $(FLAGS) main.tex
	$(LATEX) $(FLAGS) main.tex

clean:
	rm -f main.aux main.log main.out main.toc

.PHONY: all clean
