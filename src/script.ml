(* Script for experimenting with compiler code in the REPL.
 * Loads all modules except compile.ml and interpr.ml.
 *
 * To use, start ocaml or utop with something like
 *
 *    ocaml /usr/lib/ocaml/str.cma
 *
 *    (or the equivalent str.cma file on your system)
 *
 * and then "#use" this file.
 *
 * by Juliana Sarmento <js743@kent.ac.uk>
 *)

#mod_use "util.ml";;
#mod_use "tokens.ml";;
#mod_use "sourceAst.ml";;
#mod_use "typeCheck.ml";;
#mod_use "frontEnd.ml";;

#mod_use "blockStructure.ml";;
#mod_use "x86.ml";;
#mod_use "constProp.ml";;
#mod_use "unnestExp.ml";;
#mod_use "shrinkImmediates.ml";;
#mod_use "liveVarAnalysis.ml";;
#mod_use "regAlloc.ml";;
#mod_use "lineariseCfg.ml";;
#mod_use "instrSelX86.ml";;
#mod_use "compileFunction.ml";;

#mod_use "astInterp.ml";;
#mod_use "blockInterp.ml";;

