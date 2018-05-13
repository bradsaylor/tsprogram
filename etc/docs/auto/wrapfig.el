(TeX-add-style-hook
 "wrapfig"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("wrapfig" "verbose")))
   (TeX-run-style-hooks)
   (TeX-add-symbols
    "wrapoverhang"
    "WFclear"
    "caption"
    "width"
    "everypar"
    "parshape"
    "noexpand"
    "pagetotal")
   (LaTeX-add-environments
    "wraptable"
    "wrapfigure"
    "wrapfloat"
    "wrap"))
 :latex)

