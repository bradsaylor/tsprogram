(TeX-add-style-hook
 "tsp_file_funcs"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "11pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("fontenc" "T1") ("ulem" "normalem")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art11"
    "inputenc"
    "fontenc"
    "graphicx"
    "grffile"
    "longtable"
    "wrapfig"
    "rotating"
    "ulem"
    "amsmath"
    "textcomp"
    "amssymb"
    "hyperref")
   (LaTeX-add-labels
    "sec:org3ea3298"
    "sec:org7154797"
    "sec:org6b1c856"
    "sec:org3a6bf52"
    "sec:orgde9fc16"
    "sec:org8e80fee"
    "sec:orgd17368c"
    "sec:orgdb00972"
    "sec:org24f69a0"
    "sec:org1912fa6"
    "sec:org4e69236"
    "sec:org22adb97"
    "sec:org9653a68"
    "sec:org3874593"
    "sec:orgd940b60"
    "sec:org25763cc"
    "sec:orgec66e47"
    "sec:org0b09a07"
    "sec:org1f43196"
    "sec:org3b32209"
    "sec:orgaabb0a2"))
 :latex)

