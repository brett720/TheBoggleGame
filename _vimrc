set nocompatible

set noerrorbells
set novisualbell

set title
set confirm

set ignorecase
set noincsearch

set nohlsearch
set backspace=indent,eol,start

set fileformats=unix,dos,mac

set ruler
set nu
set showmode
set exrc
set nojoinspaces
set showmatch
set incsearch
set nohlsearch
set bg=light
:colorscheme slate

:set mousehide
:set undolevels=100
:set history=20
:set nolist
:set matchtime=2
:set splitbelow


set bs=2

set autoindent
set smartindent
set formatoptions=tcrq

au BufRead,BufNewFile *.{c,h,java,hpp,cpp} set expandtab
au BufRead,BufNewFile *.{c,h,java,hpp,cpp} set shiftwidth=2
au BufRead,BufNewFile *.{c,h,java,hpp,cpp} set tabstop=2

au BufRead,BufNewFile *.s set noexpandtab
au BufRead,BufNewFile *.s set shiftwidth=8
au BufRead,BufNewFile *.s set tabstop=8

set columns=80
set textwidth=80
set wrapmargin=2

:set columns=80
:set textwidth=80
:set wrapmargin=2
:set shiftround
:set scrolloff=12
:match Error /\%81v.\+/

set showmatch
syntax on
set cin

:set wildchar=<Tab>
:set wildmenu
:set wildmode=list
:set nowritebackup

:set wildignore=*.o,*.bak,*.data,*.class
autocmd BufNewFile [Mm]akefile* set formatoptions=croql comments=:#
autocmd BufNewFile .vimrc,*.vim set formatoptions=croql comments=:\"
autocmd FileType c,cpp,java set mps+==:;

map <C-J> :next <CR>
map <C-K> :prev <CR>

map <F10> <Esc>setlocal spell spelllang=en_us<CR>
map <F11> <Esc>setlocal nospell<CR>

setlocal textwidth=80
highlight Comment ctermfg=darkcyan guifg=darkcyan
