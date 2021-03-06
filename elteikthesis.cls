%% MIT License
%%
%% Version 1.0, 2018/06/06
%% Copyright (c) 2013-2018 Máté Cserép, Bálint Bognár
%%
%% Permission is hereby granted, free of charge, to any person obtaining a copy
%% of this software and associated documentation files (the "Software"), to deal
%% in the Software without restriction, including without limitation the rights
%% to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
%% copies of the Software, and to permit persons to whom the Software is
%% furnished to do so, subject to the following conditions:
%%
%% The above copyright notice and this permission notice shall be included in all
%% copies or substantial portions of the Software.
%%
%% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
%% IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
%% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
%% AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
%% LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
%% OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
%% SOFTWARE.

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{elteikthesis}[2018/06/06]

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{report}}
\ProcessOptions \relax

% Egyoldalashoz
\LoadClass[a4paper, 12pt, oneside]{report}
% Kétoldalashoz
%\LoadClass[a4paper, 12pt, twoside, openright]{report}

% ------------------------------
% Fejlécek és láblécek
\RequirePackage{fancyhdr}
\pagestyle{fancy}

% Chapter és section információk stílusának felüldefiniálása
\renewcommand{\chaptermark}[1]{\markboth{\thechapter.\ #1}{}}
\renewcommand{\sectionmark}[1]{\markright{\thesection.\ #1}{}}
% Fej- és lábléc vonalak beállítása
\renewcommand{\headrulewidth}{1pt}
\renewcommand{\footrulewidth}{0pt}

% Fejléc törlése
\fancyhead{}
% Fejléc beállítása (egyoldalashoz)
\fancyhead[C]{\slshape \leftmark}
% Fejléc beállítása (kétoldalashoz)
%\fancyhead[EC]{\slshape \leftmark}
%\fancyhead[OC]{\slshape \rightmark}

% Fejléc és lábléc távolsága a tartalomtól
\topskip = 15pt		% default: 10pt
\footskip = 20pt	% default: 30pt

% Lábléc törlése
\fancyfoot{}
% Lábléc beállítása
\fancyfoot[C]{\thepage}

% A chapter page-k mindig visszaállnak plain style-ra, ezért azt is felül kell külön definiálni.
\fancypagestyle{plain}{
	% Fejléc vonal letiltása
	\renewcommand{\headrulewidth}{0pt}
	% Teljes fejléc és lábléc törlés
	\fancyhf{}
	% Lábléc beállítása
    \fancyfoot[C]{\thepage}
}
\setlength{\headheight}{16pt}
% Üres oldalakon ne legyen fej- és lábléc
% http://www.tex.ac.uk/cgi-bin/texfaq2html?label=reallyblank
\let\origdoublepage\cleardoublepage
 \newcommand{\clearemptydoublepage}{
   \clearpage
   {\pagestyle{empty}\origdoublepage}
 }
\let\cleardoublepage\clearemptydoublepage
% ------------------------------

% ------------------------------
% Karakterkódolás, nyelv
\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage[english]{babel}
\RequirePackage{indentfirst}
% ------------------------------

% ------------------------------
% Times font használata
%\RequirePackage{txfonts}
% ------------------------------

% ------------------------------
% Grafika
\RequirePackage{graphicx}
\RequirePackage{float}
% Maximális ill. minimális méret megadása ábráknak
\RequirePackage[export]{adjustbox}
% Több ábra egy figure-on belül
\RequirePackage[center]{subfigure}
% Ábrák forgatása
\RequirePackage{rotating}

% Az EPS fájlok támogatása pdflatex használata esetén
\RequirePackage{epstopdf}
% Képek kiterjesztési prioritása
\DeclareGraphicsExtensions{.pdf,.eps,.png,.jpg}
% Képek tárolási helye
\graphicspath{{./images/}}
% ------------------------------

% ------------------------------
% Papírméret
\paperwidth 210mm
\paperheight 297mm
% ------------------------------
\f@nch@setoffs

% ------------------------------
% Margók
\RequirePackage[left=35mm, right=25mm, top=25mm, bottom=35mm]{geometry}
%\setlength{\textwidth}{150mm}
%\setlength{\textheight}{247mm}
% ------------------------------

% ------------------------------
% Térköz bekezdések közé
%\RequirePackage{parskip}
% A bekezdések első soros behúzása maradjon meg
%\setlength{\parindent}{3.5ex}
% ------------------------------

% ------------------------------
% Árva- és fattyúsorok tiltása
\clubpenalty=3000
\widowpenalty=3000
% ------------------------------

% ------------------------------
% Helyközök és tördelés
\linespread{1.5}
\frenchspacing
\sloppy

% Beállítás alternatív módon
%\RequirePackage{setspace}
%\singlespacing		% ~1.0 linespread
%\onehalfspacing	% ~1.3 linespread
%\doublespacing		% ~1.6 linespread

% Azonos sorköz használata láblácben
%\RequirePackage{footmisc}
%\setlength{\footnotesep}{\baselineskip}
% ------------------------------

% ------------------------------
% Nagybetűs szavak elválasztásának mellőzése
\uchyph=0
% ------------------------------

% ------------------------------
% Szoros térközű felsorolások
\RequirePackage{paralist}
% ------------------------------

% ------------------------------
% Matematikai mód
\RequirePackage{amsthm}
\RequirePackage{amsmath}
\DeclareMathAlphabet{\mathpzc}{OT1}{pzc}{m}{it}
% ------------------------------

% ------------------------------
% Színes szövegek
\RequirePackage{color}
\RequirePackage{xcolor}
% Színek
\definecolor{codebackg}{rgb}{0.95,0.95,0.95}
\definecolor{codecomment}{rgb}{0,0.6,0}
\colorlet{todobackg}{orange!10}
% ------------------------------

% ------------------------------
% Hivatkozások
% dvipdfm-hez
%\newcommand{\hyperrefComp}{dvipdfm}
% pdflatex-hez
\newcommand{\hyperrefComp}{}

\RequirePackage[pdfborder={0 0 0}, unicode, \hyperrefComp]{hyperref}
\RequirePackage[all]{hypcap}
\RequirePackage{url}
\RequirePackage{bookmark}
% ------------------------------

% ------------------------------
% Multirow és multicolumn táblázathoz
\RequirePackage{multirow}
% Táblázatok tördelése több oldalra
\RequirePackage{longtable}
% Celltartalmak vertikális igazítása
\RequirePackage{array}
% ------------------------------

% ------------------------------
% Felső és alsó indexek
% http://anthony.liekens.net/index.php/LaTeX/SubscriptAndSuperscriptInTextMode
\newcommand{\superscript}[1]{\ensuremath{^{\textrm{\scriptsize{#1}}}}}
\newcommand{\subscript}[1]{\ensuremath{_{\textrm{\scriptsize{#1}}}}}
% ------------------------------

% ------------------------------
% Lábjegyzet folytonos számozása fejezetek között
\RequirePackage{chngcntr}
\counterwithout{footnote}{chapter}
% Lábjegyzet oldalak közti eltörésének tiltása
\interfootnotelinepenalty=10000
% ------------------------------

% ------------------------------
% Lábjegyzet teljes körűbb támogatása (savenotes)
%\RequirePackage{footnote}
% Lábjegyzet kezelése minipage-ekben
% http://www.cs.brown.edu/system/software/latex/doc/mpfnmark.pdf
%\RequirePackage{mpfnmark}
% ------------------------------

% ------------------------------
% Függelék
\RequirePackage{appendix}
% ------------------------------

% ------------------------------
% Feliratok, tartalomjegyzék, ábrajegyzék, táblázatjegyzék
\RequirePackage[justification=centering]{caption}
\RequirePackage[subfigure]{tocloft}
% Tartalomjegyzék oldalszámozásának rejtése
\tocloftpagestyle{empty}

% ------------------------------

% ------------------------------
% Tárgymutató
\RequirePackage{makeidx}
\makeindex
% ------------------------------

% ------------------------------
% Jelölésjegyzék
\RequirePackage [refpage,noprefix]{nomencl}
\renewcommand{\nomname}{Jelölésjegyzék}
% Elemek közötti bigskip kihagyása
\setlength{\nomitemsep}{-\parsep}
% Jobbra igazítás
\renewcommand{\nomlabel}[1]{\hfil \hfil #1}
% Oldalhivatkozás megjelenése
\renewcommand{\pagedeclaration}[1]{, #1}
% Jelölésjegyzék elkészítse (még nem szúrja be)
\makenomenclature
% ------------------------------

% ------------------------------
% Algoritmusok és kódblokkok írása
\RequirePackage{algorithm}
\RequirePackage{algorithmic}
\RequirePackage{listingsutf8}
\lstset{
	basicstyle=\footnotesize\ttfamily,
	numbers=left,
    numberstyle=\tiny,
    backgroundcolor=\color{codebackg},
	keywordstyle=\color{blue},
	commentstyle=\color{codecomment},
	stepnumber=1,
	firstnumber=1,
	numbersep=5pt,
	showspaces=false,
	showstringspaces=false,
	showtabs=false,
	tabsize=2,
	breaklines=true,
	breakatwhitespace=false,
	float,
	frame=linesc,
	captionpos=b,
	morekeywords={var}
}
% Forráskódjegyzék elnevezése
\renewcommand\lstlistingname{forráskód}
% ------------------------------

% ------------------------------
% Teendőlista
% http://www.tex.ac.uk/tex-archive/help/Catalogue/entries/todonotes.html
\RequirePackage[textwidth=30mm, textsize=small, color=todobackg, linecolor=orange, colorinlistoftodos, shadow, obeyFinal]{todonotes}
\RequirePackage[displaymath, tightpage]{preview}
% A bal margóra kerüljenek a TODO-k
\reversemarginpar
\setlength{\marginparwidth}{30mm}
% ------------------------------

% ------------------------------
% Metaadatok
\RequirePackage{xparse}
\DeclareDocumentCommand{\author}{m}{\newcommand{\authorname}{#1}\renewcommand{\@author}{#1}}
\NewDocumentCommand{\degree}{m}{\newcommand{\degreename}{#1}}

\NewDocumentCommand{\supervisor}{m}{\newcommand{\supname}{#1}}
\NewDocumentCommand{\affiliation}{m}{\newcommand{\supaff}{#1}}

\NewDocumentCommand{\extsupervisor}{m}{\newcommand{\extsupname}{#1}}
\NewDocumentCommand{\extaffiliation}{m}{\newcommand{\extsupaff}{#1}}

\NewDocumentCommand{\university}{m}{\newcommand{\univname}{#1}}
\NewDocumentCommand{\faculty}{m}{\newcommand{\facname}{#1}}
\NewDocumentCommand{\department}{m}{\newcommand{\deptname}{#1}}
\NewDocumentCommand{\departmentSecondLine}{m}{\newcommand{\deptnamesec}{#1}}
\NewDocumentCommand{\city}{m}{\newcommand{\cityname}{#1}}
\NewDocumentCommand{\logo}{m}{\newcommand{\logofilename}{#1}}

\DeclareDocumentCommand{\title}{m}{\newcommand{\thesistitle}{#1}\renewcommand{\@title}{#1}}
\DeclareDocumentCommand{\date}{m}{\newcommand{\thesisyear}{#1}\renewcommand{\@date}{#1}}

% ------------------------------

% ------------------------------
% Fordítások
\DeclareDocumentCommand{\documentlang}{m}{
	\selectlanguage{#1}
	
	\ifthenelse{\equal{\detokenize{#1}}{\detokenize{magyar}}}
	{
		\newcommand{\authorlabel}{Szerző}
		\newcommand{\suplabel}{Témavezető}
		\newcommand{\intsuplabel}{Belső témavezető}
		\newcommand{\extsuplabel}{Külső témavezető}
		
		\newcommand{\deflabel}{Definíció}
		\newcommand{\theolabel}{Tétel}
		\newcommand{\remlabel}{Emlékeztető}
		\newcommand{\notelabel}{Megjegyzés}
	}
	{
		\newcommand{\authorlabel}{Author}
		\newcommand{\suplabel}{Supervisor}
		\newcommand{\intsuplabel}{Internal supervisor}
		\newcommand{\extsuplabel}{External supervisor}
		
		\newcommand{\deflabel}{Definiton}
		\newcommand{\theolabel}{Theorem}
		\newcommand{\remlabel}{Remark}
		\newcommand{\notelabel}{Note}
	}
}
% ------------------------------

% ------------------------------
% Tételek, definíciók
\newtheorem{definition}{\deflabel}
\newtheorem{theorem}{\theolabel}
\newtheorem*{remark}{\remlabel}
\newtheorem*{note}{\notelabel}
% ------------------------------

% ------------------------------
% Címlap
