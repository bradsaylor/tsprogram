(TeX-add-style-hook
 "ulem"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("ulem" "normalem")))
   (TeX-run-style-hooks)
   (TeX-add-symbols
    "sixly"
    "UL"
    "ULdepth"
    "xeqy"
    "iff"
    "uline"
    "ULset"
    "ULon"
    "hskip"
    "newline"
    "hfil"
    "hfill"
    "hss"
    "penalty"
    "ULleaders"
    "markoverwith"
    "uwave"
    "uuline"
    "sout"
    "xout"
    "dotuline"
    "dashuline"
    "useunder"
    "MakeRobust"
    "ULforem"
    "normalem"
    "em"
    "emph"
    "marginpar"
    "ULthickness"
    "x"
    "command"))
 :latex)

