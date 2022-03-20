PACKAGES := str
FLAGS := -bin-annot -g -principal -safe-string -strict-formats -strict-sequence -I . -w +a-42-4

FILES := util tokens sourceAst typeCheck frontEnd constProp unnestExp \
blockStructure shrinkImmediates liveVarAnalysis regAlloc lineariseCfg x86 \
instrSelX86 compileFunction astInterp interp compile
FILES_ML := $(addsuffix .ml,$(FILES))
# Can't use wildcard because it doesn't list files in the topsorted order which
# the OCaml link step requires... pretty silly that ocamlc can't do that itself.
#FILES_ML := $(filter-out script.ml,$(wildcard *.ml))

FILES_CMI := $(patsubst %.ml,%.cmi,$(FILES_ML))
FILES_CMT := $(patsubst %.ml,%.cmt,$(FILES_ML))
FILES_CMTI := $(patsubst %.ml,%.cmti,$(FILES_ML))
FILES_CMO := $(patsubst %.ml,%.cmo,$(FILES_ML))
FILES_CMX := $(patsubst %.ml,%.cmx,$(FILES_ML))
FILES_O := $(patsubst %.ml,%.o,$(FILES_ML))

.PHONY : all
all : interp.byte compile.byte

interp.byte : $(FILES_CMO)
	ocamlfind ocamlc -linkpkg -package $(PACKAGES) $(filter-out compile.cmo,$(FILES_CMO)) -o $@

interp.native : $(FILES_CMX)
	ocamlfind ocamlopt -linkpkg -package $(PACKAGES) $(filter-out compile.cmx,$(FILES_CMX)) -o $@

compile.byte : $(FILES_CMO)
	ocamlfind ocamlc -linkpkg -package $(PACKAGES) $(filter-out interp.cmo,$(FILES_CMO)) -o $@

compile.native : $(FILES_CMX)
	ocamlfind ocamlopt -linkpkg -package $(PACKAGES) $(filter-out interp.cmx,$(FILES_CMX)) -o $@

%.cmi : %.mli
	ocamlfind ocamlc -package $(PACKAGES) $(FLAGS) -o $@ -c $<

%.cmo : %.ml
	ocamlfind ocamlc -package $(PACKAGES) $(FLAGS) -o $@ -c $<

%.cmx : %.ml
	ocamlfind ocamlopt -package $(PACKAGES) $(FLAGS) -o $@ -c $<

.PHONY : clean
clean :
	rm -f $(FILES_CMI) $(FILES_CMTI) $(FILES_CMT) $(FILES_CMO) $(FILES_CMX) $(FILES_O) compile.byte compile.native interp.byte interp.native

.depend :
	ocamlfind ocamldep $(FILES_ML) > $@

include .depend
