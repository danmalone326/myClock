MD_MAX72XX::fontType_t clockFont[] PROGMEM = 
{
	0, 	// 0 - 'Empty Cell'
	5, 62, 91, 79, 91, 62, 	// 1 - 'Sad Smiley'
	5, 62, 107, 79, 107, 62, 	// 2 - 'Happy Smiley'
	5, 28, 62, 124, 62, 28, 	// 3 - 'Heart'
	5, 24, 60, 126, 60, 24, 	// 4 - 'Diamond'
	5, 28, 87, 125, 87, 28, 	// 5 - 'Clubs'
	5, 28, 94, 127, 94, 28, 	// 6 - 'Spades'
	4, 0, 24, 60, 24, 	// 7 - 'Bullet Point'
	5, 255, 231, 195, 231, 255, 	// 8 - 'Rev Bullet Point'
	4, 0, 24, 36, 24, 	// 9 - 'Hollow Bullet Point'
	5, 255, 231, 219, 231, 255, 	// 10 - 'Rev Hollow BP'
	5, 48, 72, 58, 6, 14, 	// 11 - 'Male'
	5, 38, 41, 121, 41, 38, 	// 12 - 'Female'
	5, 64, 127, 5, 5, 7, 	// 13 - 'Music Note 1'
	5, 64, 127, 5, 37, 63, 	// 14 - 'Music Note 2'
	5, 90, 60, 231, 60, 90, 	// 15 - 'Snowflake'
	5, 127, 62, 28, 28, 8, 	// 16 - 'Right Pointer'
	5, 8, 28, 28, 62, 127, 	// 17 - 'Left Pointer'
	5, 20, 34, 127, 34, 20, 	// 18 - 'UpDown Arrows'
	5, 255, 255, 255, 255, 255, 	// 19 - 'Full Block'
	5, 240, 240, 240, 240, 240, 	// 20 - 'Half Block Bottom'
	3, 255, 255, 255, 	// 21 - 'Half Block LHS'
	5, 0, 0, 0, 255, 255, 	// 22 - 'Half Block RHS'
	5, 15, 15, 15, 15, 15, 	// 23 - 'Half Block Top'
	5, 8, 4, 126, 4, 8, 	// 24 - 'Up Arrow'
	5, 16, 32, 126, 32, 16, 	// 25 - 'Down Arrow'
	5, 8, 8, 42, 28, 8, 	// 26 - 'Right Arrow'
	5, 8, 28, 42, 8, 8, 	// 27 - 'Left Arrow'
	5, 170, 0, 85, 0, 170, 	// 28 - '30% shading'
	5, 170, 85, 170, 85, 170, 	// 29 - '50% shading'
	5, 48, 56, 62, 56, 48, 	// 30 - 'Up Pointer'
	5, 6, 14, 62, 14, 6, 	// 31 - 'Down Pointer'
	1, 0, 	// 32  - 'Space'
	1, 95, 	// 33 - '!'
	3, 7, 0, 7, 	// 34 - '""'
	5, 20, 127, 20, 127, 20, 	// 35 - '#'
	5, 68, 74, 255, 74, 50, 	// 36 - '$'
	5, 99, 19, 8, 100, 99, 	// 37 - '%'
	5, 54, 73, 73, 54, 72, 	// 38 - '&'
	1, 7, 	// 39 - '''
	3, 62, 65, 65, 	// 40 - '('
	3, 65, 65, 62, 	// 41 - ')'
	5, 8, 42, 28, 42, 8, 	// 42 - '*'
	5, 8, 8, 62, 8, 8, 	// 43 - '+'
	3, 96, 224, 0, 	// 44'
	4, 8, 8, 8, 8, 	// 45 - '-'
	2, 96, 96, 	// 46 - '.'
	5, 96, 16, 8, 4, 3, 	// 47 - '/'
	5, 62, 81, 73, 69, 62, 	// 48 - '0'
  5, 0, 4, 2, 127, 0,    // 49 - '1'
	5, 113, 73, 73, 73, 70, 	// 50 - '2'
	5, 65, 73, 73, 73, 54, 	// 51 - '3'
	5, 15, 8, 8, 8, 127, 	// 52 - '4'
	5, 79, 73, 73, 73, 49, 	// 53 - '5'
	5, 62, 73, 73, 73, 48, 	// 54 - '6'
	5, 1, 1, 1, 1, 127, 	// 55 - '7'
	5, 54, 73, 73, 73, 54, 	// 56 - '8'
	5, 6, 73, 73, 73, 62, 	// 57 - '9'
	1, 34, 	// 58 - ':'
	2, 108, 236, 	// 59 - ';'
	3, 8, 20, 34, 	// 60 - '<'
	4, 20, 20, 20, 20, 	// 61 - '='
	3, 34, 20, 8, 	// 62 - '>'
	5, 1, 89, 9, 9, 6, 	// 63 - '?'
	5, 62, 65, 93, 89, 78, 	// 64 - '@'
	5, 126, 9, 9, 9, 126, 	// 65 - 'A'
	5, 127, 73, 73, 73, 54, 	// 66 - 'B'
	5, 62, 65, 65, 65, 65, 	// 67 - 'C'
	5, 127, 65, 65, 65, 62, 	// 68 - 'D'
	5, 127, 73, 73, 73, 65, 	// 69 - 'E'
	5, 127, 9, 9, 9, 1, 	// 70 - 'F'
	5, 62, 65, 65, 73, 121, 	// 71 - 'G'
	5, 127, 8, 8, 8, 127, 	// 72 - 'H'
	3, 65, 127, 65, 	// 73 - 'I'
	5, 48, 65, 65, 65, 63, 	// 74 - 'J'
	5, 127, 8, 20, 34, 65, 	// 75 - 'K'
	5, 127, 64, 64, 64, 64, 	// 76 - 'L'
	5, 127, 2, 12, 2, 127, 	// 77 - 'M'
	5, 127, 4, 8, 16, 127, 	// 78 - 'N'
	5, 62, 65, 65, 65, 62, 	// 79 - 'O'
	5, 127, 9, 9, 9, 6, 	// 80 - 'P'
	5, 62, 65, 65, 97, 126, 	// 81 - 'Q'
	5, 127, 9, 25, 41, 70, 	// 82 - 'R'
	5, 70, 73, 73, 73, 49, 	// 83 - 'S'
	5, 1, 1, 127, 1, 1, 	// 84 - 'T'
	5, 63, 64, 64, 64, 63, 	// 85 - 'U'
	5, 31, 32, 64, 32, 31, 	// 86 - 'V'
	5, 63, 64, 56, 64, 63, 	// 87 - 'W'
	5, 99, 20, 8, 20, 99, 	// 88 - 'X'
	5, 3, 4, 120, 4, 3, 	// 89 - 'Y'
	5, 97, 81, 73, 69, 67, 	// 90 - 'Z'
	3, 127, 65, 65, 	// 91 - '['
	5, 3, 4, 8, 16, 96, 	// 92 - '\'
	3, 65, 65, 127, 	// 93 - ']'
	5, 4, 2, 1, 2, 4, 	// 94 - '^'
	4, 128, 128, 128, 128, 	// 95 - '_'
	3, 1, 2, 4, 	// 96 - '`'
	4, 56, 68, 68, 124, 	// 97 - 'a'
	4, 127, 68, 68, 56, 	// 98 - 'b'
	4, 56, 68, 68, 68, 	// 99 - 'c'
	4, 56, 68, 68, 127, 	// 100 - 'd'
	4, 56, 84, 84, 88, 	// 101 - 'e'
	4, 4, 126, 5, 1, 	// 102 - 'f'
	4, 24, 164, 164, 124, 	// 103 - 'g'
	4, 127, 4, 4, 120, 	// 104 - 'h'
	1, 125, 	// 105 - 'i'
	3, 132, 133, 124, 	// 106 - 'j'
	4, 127, 16, 40, 68, 	// 107 - 'k'
	1, 127, 	// 108 - 'l'
	5, 124, 4, 120, 4, 120, 	// 109 - 'm'
	4, 124, 4, 4, 120, 	// 110 - 'n'
	4, 56, 68, 68, 56, 	// 111 - 'o'
	4, 252, 36, 36, 24, 	// 112 - 'p'
	4, 24, 36, 36, 252, 	// 113 - 'q'
	4, 124, 4, 4, 8, 	// 114 - 'r'
	4, 88, 84, 84, 52, 	// 115 - 's'
	3, 4, 127, 4, 	// 116 - 't'
	4, 60, 64, 64, 124, 	// 117 - 'u'
	4, 28, 32, 64, 124, 	// 118 - 'v'
	5, 60, 64, 48, 64, 60, 	// 119 - 'w'
	4, 108, 16, 16, 108, 	// 120 - 'x'
	4, 28, 160, 160, 124, 	// 121 - 'y'
	4, 100, 84, 84, 76, 	// 122 - 'z'
	4, 8, 54, 65, 65, 	// 123 - '{'
	1, 127, 	// 124 - '|'
	4, 65, 65, 54, 8, 	// 125 - '}'
	4, 2, 1, 2, 1, 	// 126 - '~'
	5, 127, 65, 65, 65, 127, 	// 127 - 'Hollow Block'
	5, 62, 85, 85, 85, 65, 	// 128 - 'Euro symbol'
	5, 56, 68, 68, 56, 68, 	// 129 - 'Alpha'
	5, 124, 42, 42, 62, 20, 	// 130 - 'Beta'
	5, 126, 2, 2, 6, 6, 	// 131 - 'Gamma'
	5, 2, 126, 2, 126, 2, 	// 132 - 'Pi'
	5, 99, 85, 73, 65, 99, 	// 133 - 'Sigma'
	5, 56, 68, 68, 60, 4, 	// 134 - 'Theta'
	5, 64, 126, 32, 30, 32, 	// 135 - 'mu'
	5, 6, 2, 126, 2, 2, 	// 136 - 'Tau'
	8, 99, 19, 8, 100, 99, 0, 96, 96, 	// 137 - 'Percent 00'
	5, 42, 42, 42, 42, 42, 	// 138 - '3 Bar Equals'
	3, 81, 74, 68, 	// 139 - '>='
	3, 68, 74, 81, 	// 140 - '<='
	5, 0, 0, 255, 1, 3, 	// 141 - 'Top of Integral'
	3, 224, 128, 255, 	// 142 - 'Bot of Integral'
	5, 54, 18, 54, 36, 54, 	// 143 - 'Wavy ='
	3, 2, 5, 2, 	// 144 - 'Degree'
	2, 24, 24, 	// 145 - 'Math Product'
	2, 16, 16, 	// 146 - 'Short Dash'
	5, 48, 64, 255, 1, 1, 	// 147 - 'Square Root'
	4, 31, 1, 1, 30, 	// 148 - 'Superscript n'
	0, 	// 149
	5, 0, 0, 0, 0, 0, 	// 150  
	0, 	// 151  
	0, 	// 152
	9, 1, 1, 127, 1, 127, 2, 12, 2, 127, 	// 153 - 'Trademark'
	0, 	// 154
	0, 	// 155
	0, 	// 156
	0, 	// 157
	0, 	// 158
	0, 	// 159
	1, 0, 	// 160 - ' Non-breaking space'
	1, 125, 	// 161 - '¡ Inverted Exclamation Mark'
	4, 24, 36, 126, 36, 	// 162 - '¢ Cent sign'
	4, 68, 126, 69, 65, 	// 163 - '£ Pound sign'
	5, 34, 28, 20, 28, 34, 	// 164 - '¤ Currency sign'
	5, 1, 42, 124, 42, 1, 	// 165 - '¥ Yen sign'
	1, 119, 	// 166 - '¦ Broken bar'
	4, 78, 85, 85, 57, 	// 167 - '§ Section sign'
	3, 2, 0, 2, 	// 168 - '¨ Diaeresis (Umlaut)'
	7, 126, 129, 189, 165, 165, 129, 126, 	// 169 - '© Copyright sign'
	3, 38, 41, 47, 	// 170 - 'ª Feminine Ordinal Indicator'
	5, 8, 20, 42, 20, 34, 	// 171 - '« Left-pointing double angle quotation mark'
	4, 8, 8, 8, 24, 	// 172 - '¬ Not sign'
	3, 8, 8, 8, 	// 173 - ' Soft hyphen'
	7, 126, 129, 189, 149, 169, 129, 126, 	// 174 - '® Registered sign'
	5, 1, 1, 1, 1, 1, 	// 175 - '¯ macron'
	3, 2, 5, 2, 	// 176 - '° Degree symbol'
	3, 36, 46, 36, 	// 177 - '± Plus-minus sign'
	3, 25, 21, 18, 	// 178 - '² Superscript two'
	3, 21, 21, 10, 	// 179 - '³ Superscript three'
	2, 2, 1, 	// 180 - '´ Acute accent'
	4, 248, 32, 64, 120, 	// 181 - 'µ Micro sign'
	5, 6, 9, 127, 1, 127, 	// 182 - 'Pilcrow sign'
	2, 24, 24, 	// 183 - '· Middle dot'
	4, 0, 128, 160, 192, 	// 184 - '¸ Cedilla'
	3, 18, 31, 16, 	// 185 - '¹ Superscript one'
	3, 38, 41, 38, 	// 186 - 'º Masculine ordinal indicator'
	5, 34, 20, 42, 20, 8, 	// 187 - '» Right-pointing double angle quotation mark'
	8, 64, 47, 16, 8, 4, 30, 17, 124, 	// 188 - '¼ Vulgar fraction one quarter'
	8, 64, 47, 16, 8, 4, 98, 85, 76, 	// 189 - '½ Vulgar fraction one half'
	9, 21, 85, 63, 16, 8, 4, 30, 17, 124, 	// 190 - '¾ Vulgar fraction three quarters'
	5, 48, 72, 72, 77, 64, 	// 191 - '¿ Inverted Question Mark'
	5, 120, 21, 22, 20, 120, 	// 192 - 'À Latin Capital Letter A with grave'
	5, 120, 20, 22, 21, 120, 	// 193 - 'Á Latin Capital letter A with acute'
	5, 122, 21, 20, 21, 122, 	// 194 - 'Â Latin Capital letter A with circumflex'
	5, 120, 22, 21, 22, 121, 	// 195 - 'Ã Latin Capital letter A with tilde'
	5, 120, 21, 20, 21, 120, 	// 196 - 'Ä Latin Capital letter A with diaeresis'
	5, 120, 20, 21, 20, 120, 	// 197 - 'Å Latin Capital letter A with ring above'
	7, 126, 9, 9, 127, 73, 73, 65, 	// 198 - 'Æ Latin Capital letter Æ'
	5, 158, 161, 97, 33, 33, 	// 199 - 'Ç Latin Capital letter C with cedilla'
	5, 124, 84, 85, 70, 68, 	// 200 - 'È Latin Capital letter E with grave'
	5, 124, 84, 86, 69, 68, 	// 201 - 'É Latin Capital letter E with acute'
	5, 126, 85, 84, 69, 70, 	// 202 - 'Ê Latin Capital letter E with circumflex'
	5, 124, 85, 84, 69, 68, 	// 203 - 'Ë Latin Capital letter E with diaeresis'
	3, 69, 126, 68, 	// 204 - 'Ì Latin Capital letter I with grave'
	3, 68, 126, 69, 	// 205 - 'Í Latin Capital letter I with acute'
	3, 70, 125, 70, 	// 206 - 'Î Latin Capital letter I with circumflex'
	3, 69, 124, 69, 	// 207 - 'Ï Latin Capital letter I with diaeresis'
	5, 8, 127, 73, 65, 62, 	// 208 - 'Ð Latin Capital letter Eth'
	5, 124, 10, 17, 34, 125, 	// 209 - 'Ñ Latin Capital letter N with tilde'
	5, 56, 68, 69, 70, 56, 	// 210 - 'Ò Latin Capital letter O with grave'
	5, 56, 68, 70, 69, 56, 	// 211 - 'Ó Latin Capital letter O with acute'
	5, 58, 69, 68, 69, 58, 	// 212 - 'Ô Latin Capital letter O with circumflex'
	5, 56, 70, 69, 70, 57, 	// 213 - 'Õ Latin Capital letter O with tilde'
	5, 56, 69, 68, 69, 56, 	// 214 - 'Ö Latin Capital letter O with diaeresis'
	5, 34, 20, 8, 20, 34, 	// 215 - '× Multiplication sign'
	5, 124, 98, 90, 70, 62, 	// 216 - 'Ø Latin Capital letter O with stroke'
	5, 60, 64, 65, 66, 60, 	// 217 - 'Ù Latin Capital letter U with grave'
	5, 60, 64, 66, 65, 60, 	// 218 - 'Ú Latin Capital letter U with acute'
	5, 60, 66, 65, 66, 60, 	// 219 - 'Û Latin Capital Letter U with circumflex'
	5, 60, 65, 64, 65, 60, 	// 220 - 'Ü Latin Capital Letter U with diaeresis'
	5, 2, 4, 122, 5, 2, 	// 221 - 'Ý Latin Capital Letter Y with acute'
	4, 63, 18, 18, 12, 	// 222 - 'Þ Latin Capital Letter Thorn'
	5, 126, 73, 73, 78, 48, 	// 223 - 'ß Latin Small Letter sharp S'
	4, 56, 69, 70, 124, 	// 224 - 'à Latin Small Letter A with grave'
	4, 56, 68, 70, 125, 	// 225 - 'á Latin Small Letter A with acute'
	4, 56, 70, 69, 126, 	// 226 - 'â Latin Small Letter A with circumflex'
	4, 58, 69, 70, 125, 	// 227 - 'ã Latin Small Letter A with tilde'
	4, 56, 69, 68, 125, 	// 228 - 'ä Latin Small Letter A with diaeresis'
	4, 48, 74, 77, 122, 	// 229 - 'å Latin Small Letter A with ring above'
	7, 32, 84, 84, 56, 84, 84, 88, 	// 230 - 'æ Latin Small Letter Æ'
	4, 156, 162, 98, 34, 	// 231 - 'ç Latin Small Letter C with cedilla'
	4, 56, 85, 86, 88, 	// 232 - 'è Latin Small Letter E with grave'
	4, 56, 84, 86, 89, 	// 233 - 'é Latin Small Letter E with acute'
	4, 56, 86, 85, 90, 	// 234 - 'ê Latin Small Letter E with circumflex'
	4, 56, 85, 84, 89, 	// 235 - 'ë Latin Small Letter E with diaeresis'
	2, 1, 122, 	// 236 - 'ì Latin Small Letter I with grave'
	2, 122, 1, 	// 237 - 'í Latin Small Letter I with acute'
	3, 2, 121, 2, 	// 238 - 'î Latin Small Letter I with circumflex'
	3, 2, 120, 2, 	// 239 - 'ï Latin Small Letter I with diaeresis'
	4, 48, 75, 75, 60, 	// 240 - 'ð Latin Small Letter Eth'
	4, 122, 9, 10, 113, 	// 241 - 'ñ Latin Small Letter N with tilde'
	4, 48, 73, 74, 48, 	// 242 - 'ò Latin Small Letter O with grave'
	4, 48, 72, 74, 49, 	// 243 - 'ó Latin Small Letter O with acute'
	4, 48, 74, 73, 50, 	// 244 - 'ô Latin Small Letter O with circumflex'
	4, 50, 73, 74, 49, 	// 245 - 'õ Latin Small Letter O with tilde'
	4, 57, 68, 68, 57, 	// 246 - 'ö Latin Small Letter O with diaeresis'
	5, 8, 8, 42, 8, 8, 	// 247 - '÷ Division sign'
	4, 56, 84, 76, 56, 	// 248 - 'ø Latin Small Letter O with stroke'
	4, 56, 65, 66, 120, 	// 249 - 'ù Latin Small Letter U with grave'
	4, 56, 64, 66, 121, 	// 250 - 'ú Latin Small Letter U with acute'
	4, 56, 66, 65, 122, 	// 251 - 'û Latin Small Letter U with circumflex'
	4, 58, 64, 64, 122, 	// 252 - 'ü Latin Small Letter U with diaeresis'
	4, 24, 160, 162, 121, 	// 253 - 'ý Latin Small Letter Y with acute'
	4, 252, 40, 40, 16, 	// 254 - 'þ Latin Small Letter Thorn'
	0, 	// 255
};


MD_MAX72XX::fontType_t fourWide[] PROGMEM = 
{
  0,  // 0      
  0,  // 1      
  0,  // 2      
  0,  // 3      
  0,  // 4      
  0,  // 5      
  0,  // 6      
  0,  // 7      
  0,  // 8      
  0,  // 9      
  0,  // 10      
  0,  // 11      
  0,  // 12      
  0,  // 13      
  0,  // 14      
  0,  // 15      
  0,  // 16      
  0,  // 17      
  0,  // 18      
  0,  // 19      
  0,  // 20      
  0,  // 21      
  0,  // 22      
  0,  // 23      
  0,  // 24      
  0,  // 25      
  0,  // 26      
  0,  // 27      
  0,  // 28      
  0,  // 29      
  0,  // 30      
  0,  // 31      
  1, 0,   // 32       - space
  0,  // 33      
  0,  // 34      
  0,  // 35      
  0,  // 36      
  0,  // 37      
  0,  // 38      
  0,  // 39      
  0,  // 40      
  0,  // 41      
  0,  // 42      
  0,  // 43      
  0,  // 44      
  0,  // 45      
  0,  // 46      
  4, 96, 16, 8, 6,  // 47      - /
  4, 60, 82, 74, 60,  // 48     - 0
  4, 0, 68, 126, 64,  // 49      - 1
  4, 100, 82, 82, 76,   // 50      - 2
  4, 66, 74, 74, 52,  // 51     - 3
  4, 30, 16, 124, 16,   // 52      - 4
  4, 78, 74, 74, 50,  // 53     - 5  
  4, 60, 74, 74, 50,  // 54     - 6
  4, 2, 114, 10, 6,   // 55      - 7
  4, 52, 74, 74, 52,  // 56     - 8
  4, 76, 82, 82, 60,  // 57     - 9
  1, 36,  // 58      - :
  0,  // 59      
  0,  // 60      
  0,  // 61      
  0,  // 62      
  0,  // 63      
  0,  // 64      
  4, 124, 18, 18, 124,  // 65      - A
  0,  // 66      
  4, 60, 66, 66, 66,  // 67      - C
  0,  // 68      
  0,  // 69      
  4, 126, 10, 10, 2,  // 70      - F
  0,  // 71      
  0,  // 72      
  0,  // 73      
  0,  // 74      
  0,  // 75      
  0,  // 76      
  4, 126, 12, 12, 126,  // 77      - M
  0,  // 78      
  0,  // 79      
  4, 126, 18, 18, 12,   // 80      - P
  0,  // 81      
  0,  // 82      
  0,  // 83      
  4, 2, 2, 126, 2,  // 84      - T
  4, 126, 64, 64, 126,  // 85      - U
  0,  // 86      
  0,  // 87      
  0,  // 88      
  0,  // 89      
  4, 98, 82, 74, 70,  // 90      - Z
  0,  // 91      
  0,  // 92      
  0,  // 93      
  0,  // 94      
  0,  // 95      
  0,  // 96      
  0,  // 97      
  0,  // 98      
  0,  // 99      
  0,  // 100      
  0,  // 101      
  0,  // 102      
  0,  // 103      
  0,  // 104      
  0,  // 105      
  0,  // 106      
  0,  // 107      
  1, 126,   // 108      - lower L or narrow 1
  0,  // 109      
  0,  // 110      
  0,  // 111      
  0,  // 112      
  0,  // 113      
  0,  // 114      
  0,  // 115      
  0,  // 116      
  0,  // 117      
  0,  // 118      
  0,  // 119      
  0,  // 120      
  0,  // 121      
  0,  // 122      
  0,  // 123      
  0,  // 124      
  0,  // 125      
  0,  // 126      
  0,  // 127      
  0,  // 128      
  0,  // 129      
  0,  // 130      
  0,  // 131      
  0,  // 132      
  0,  // 133      
  0,  // 134      
  0,  // 135      
  0,  // 136      
  0,  // 137      
  0,  // 138      
  0,  // 139      
  0,  // 140      
  0,  // 141      
  0,  // 142      
  0,  // 143      
  0,  // 144      
  0,  // 145      
  0,  // 146      
  0,  // 147      
  0,  // 148      
  0,  // 149      
  0,  // 150      
  0,  // 151      
  0,  // 152      
  0,  // 153      
  0,  // 154      
  0,  // 155      
  0,  // 156      
  0,  // 157      
  0,  // 158      
  0,  // 159      
  0,  // 160      
  0,  // 161      
  0,  // 162      
  0,  // 163      
  0,  // 164      
  0,  // 165      
  0,  // 166      
  0,  // 167      
  0,  // 168      
  0,  // 169      
  0,  // 170      
  0,  // 171      
  0,  // 172      
  0,  // 173      
  0,  // 174      
  0,  // 175      
  3, 14, 10, 14,  // 176      - degrees
  0,  // 177      
  0,  // 178      
  0,  // 179      
  0,  // 180      
  0,  // 181      
  0,  // 182      
  0,  // 183      
  0,  // 184      
  0,  // 185      
  0,  // 186      
  0,  // 187      
  0,  // 188      
  0,  // 189      
  0,  // 190      
  0,  // 191      
  0,  // 192      
  0,  // 193      
  0,  // 194      
  0,  // 195      
  0,  // 196      
  0,  // 197      
  0,  // 198      
  0,  // 199      
  0,  // 200      
  0,  // 201      
  0,  // 202      
  0,  // 203      
  0,  // 204      
  0,  // 205      
  0,  // 206      
  0,  // 207      
  0,  // 208      
  0,  // 209      
  0,  // 210      
  0,  // 211      
  0,  // 212      
  0,  // 213      
  0,  // 214      
  0,  // 215      
  0,  // 216      
  0,  // 217      
  0,  // 218      
  0,  // 219      
  0,  // 220      
  0,  // 221      
  0,  // 222      
  0,  // 223      
  0,  // 224      
  0,  // 225      
  0,  // 226      
  0,  // 227      
  0,  // 228      
  0,  // 229      
  0,  // 230      
  0,  // 231      
  0,  // 232      
  0,  // 233      
  0,  // 234      
  0,  // 235      
  0,  // 236      
  0,  // 237      
  0,  // 238      
  0,  // 239      
  0,  // 240      
  0,  // 241      
  0,  // 242      
  0,  // 243      
  0,  // 244      
  0,  // 245      
  0,  // 246      
  0,  // 247      
  0,  // 248      
  0,  // 249      
  0,  // 250      
  0,  // 251      
  0,  // 252      
  0,  // 253      
  0,  // 254      
  0,  // 255
};



const MD_MAX72XX::fontType_t threeByFive[] PROGMEM = {
    0, // char 0
    0, // char 1
    0, // char 2
    0, // char 3
    0, // char 4
    0, // char 5
    0, // char 6
    0, // char 7
    0, // char 8
    0, // char 9
    0, // char 10
    0, // char 11
    0, // char 12
    0, // char 13
    0, // char 14
    0, // char 15
    0, // char 16
    0, // char 17
    0, // char 18
    0, // char 19
    0, // char 20
    0, // char 21
    0, // char 22
    0, // char 23
    0, // char 24
    0, // char 25
    0, // char 26
    0, // char 27
    0, // char 28
    0, // char 29
    0, // char 30
    0, // char 31
    3, 0x0, 0x0, 0x0, // char 32 - " "
    3, 0x0, 0xb8, 0x0, // char 33 - "!"
    3, 0x0, 0x18, 0x0, // char 34 - """
    3, 0xf8, 0x50, 0xf8, // char 35 - "#"
    3, 0xb8, 0xfc, 0xe8, // char 36 - "$"
    3, 0xc8, 0x20, 0x98, // char 37 - "%"
    3, 0xd0, 0xa8, 0x90, // char 38 - "&"
    3, 0x0, 0x18, 0x0, // char 39 - "'"
    3, 0x0, 0x70, 0x88, // char 40 - "("
    3, 0x88, 0x70, 0x0, // char 41 - ")"
    3, 0x50, 0x20, 0x50, // char 42 - "*"
    3, 0x20, 0x70, 0x20, // char 43 - "+"
    3, 0x0, 0x80, 0x40, // char 44 - ","
    3, 0x20, 0x20, 0x20, // char 45 - "-"
    3, 0x0, 0x40, 0x0, // char 46 - "."
    3, 0xc0, 0x20, 0x18, // char 47 - "/"
    3, 0xf8, 0x88, 0xf8, // char 48 - "0"
    3, 0x90, 0xf8, 0x80, // char 49 - "1"
    3, 0xe8, 0xa8, 0xb8, // char 50 - "2"
    3, 0x88, 0xa8, 0xf8, // char 51 - "3"
    3, 0x60, 0x50, 0xf8, // char 52 - "4"
    3, 0xb8, 0xa8, 0xe8, // char 53 - "5"
    3, 0xf8, 0xa8, 0xe8, // char 54 - "6"
    3, 0x8, 0xc8, 0x38, // char 55 - "7"
    3, 0xf8, 0xa8, 0xf8, // char 56 - "8"
    3, 0xb8, 0xa8, 0xf8, // char 57 - "9"
    3, 0x0, 0x50, 0x0, // char 58 - ":"
    3, 0x80, 0x50, 0x0, // char 59 - ";"
    3, 0x20, 0x50, 0x88, // char 60 - "<"
    3, 0x50, 0x50, 0x50, // char 61 - "="
    3, 0x88, 0x50, 0x20, // char 62 - ">"
    3, 0x0, 0xa8, 0x38, // char 63 - "?"
    3, 0x70, 0xa8, 0x90, // char 64 - "@"
    3, 0xf0, 0x48, 0xf0, // char 65 - "A"
    3, 0xf8, 0xa8, 0x50, // char 66 - "B"
    3, 0x70, 0x88, 0x50, // char 67 - "C"
    3, 0xf8, 0x88, 0x70, // char 68 - "D"
    3, 0xf8, 0xa8, 0x88, // char 69 - "E"
    3, 0xf8, 0x28, 0x8, // char 70 - "F"
    3, 0x70, 0x88, 0xe8, // char 71 - "G"
    3, 0xf8, 0x20, 0xf8, // char 72 - "H"
    3, 0x88, 0xf8, 0x88, // char 73 - "I"
    3, 0x48, 0x88, 0x78, // char 74 - "J"
    3, 0xf8, 0x20, 0xd8, // char 75 - "K"
    3, 0xf8, 0x80, 0x80, // char 76 - "L"
    3, 0xf8, 0x10, 0xf8, // char 77 - "M"
    3, 0xf8, 0x8, 0xf0, // char 78 - "N"
    3, 0x70, 0x88, 0x70, // char 79 - "O"
    3, 0xf8, 0x48, 0x30, // char 80 - "P"
    3, 0x70, 0xc8, 0xb0, // char 81 - "Q"
    3, 0xf8, 0x48, 0xb0, // char 82 - "R"
    3, 0x90, 0xa8, 0x48, // char 83 - "S"
    3, 0x8, 0xf8, 0x8, // char 84 - "T"
    3, 0x78, 0x80, 0x78, // char 85 - "U"
    3, 0xf8, 0x40, 0x38, // char 86 - "V"
    3, 0xf8, 0x40, 0xf8, // char 87 - "W"
    3, 0xd8, 0x20, 0xd8, // char 88 - "X"
    3, 0x18, 0xe0, 0x18, // char 89 - "Y"
    3, 0xc8, 0xa8, 0x98, // char 90 - "Z"
    3, 0x0, 0xf8, 0x88, // char 91 - "["
    3, 0x18, 0x20, 0xc0, // char 92 - "\"
    3, 0x88, 0xf8, 0x0, // char 93 - "]"
    3, 0x10, 0x8, 0x10, // char 94 - "^"
    3, 0x80, 0x80, 0x80, // char 95 - "_"
    3, 0x8, 0x10, 0x0, // char 96 - "`"
    3, 0x40, 0xa8, 0xf0, // char 97 - "a"
    3, 0xf8, 0xa0, 0x40, // char 98 - "b"
    3, 0x60, 0x90, 0x90, // char 99 - "c"
    3, 0x40, 0xa0, 0xf8, // char 100 - "d"
    3, 0x70, 0xa8, 0xb0, // char 101 - "e"
    3, 0xf0, 0x28, 0x8, // char 102 - "f"
    3, 0x90, 0xa8, 0x70, // char 103 - "g"
    3, 0xf0, 0x20, 0xc0, // char 104 - "h"
    3, 0xa0, 0xe8, 0x80, // char 105 - "i"
    3, 0x40, 0x80, 0x68, // char 106 - "j"
    3, 0xf0, 0x20, 0xd0, // char 107 - "k"
    3, 0x88, 0xf8, 0x80, // char 108 - "l"
    3, 0xf0, 0x20, 0xf0, // char 109 - "m"
    3, 0xf0, 0x10, 0xe0, // char 110 - "n"
    3, 0x60, 0x90, 0x60, // char 111 - "o"
    3, 0xf0, 0x50, 0x20, // char 112 - "p"
    3, 0x20, 0x50, 0xf0, // char 113 - "q"
    3, 0xf0, 0x10, 0x20, // char 114 - "r"
    3, 0x10, 0xa8, 0x40, // char 115 - "s"
    3, 0x78, 0x90, 0x80, // char 116 - "t"
    3, 0x70, 0x80, 0x70, // char 117 - "u"
    3, 0xf0, 0x40, 0x30, // char 118 - "v"
    3, 0xf0, 0x40, 0xf0, // char 119 - "w"
    3, 0xd0, 0x20, 0xd0, // char 120 - "x"
    3, 0x90, 0xa0, 0x70, // char 121 - "y"
    3, 0x90, 0xd0, 0xb0, // char 122 - "z"
    3, 0x20, 0xd8, 0x88, // char 123 - "{"
    3, 0x0, 0xf8, 0x0, // char 124 - "|"
    3, 0x88, 0xd8, 0x20, // char 125 - "}"
    3, 0x8, 0x10, 0x8, // char 126 - "~"
    3, 0x10, 0x28, 0x10, // char 127 - ""
    0, // char 128
    0, // char 129
    0, // char 130
    0, // char 131
    0, // char 132
    0, // char 133
    0, // char 134
    0, // char 135
    0, // char 136
    0, // char 137
    0, // char 138
    0, // char 139
    0, // char 140
    0, // char 141
    0, // char 142
    0, // char 143
    0, // char 144
    0, // char 145
    0, // char 146
    0, // char 147
    0, // char 148
    0, // char 149
    0, // char 150
    0, // char 151
    0, // char 152
    0, // char 153
    0, // char 154
    0, // char 155
    0, // char 156
    0, // char 157
    0, // char 158
    0, // char 159
    0, // char 160
    0, // char 161
    0, // char 162
    0, // char 163
    0, // char 164
    0, // char 165
    0, // char 166
    0, // char 167
    0, // char 168
    0, // char 169
    0, // char 170
    0, // char 171
    0, // char 172
    0, // char 173
    0, // char 174
    0, // char 175
    0, // char 176
    0, // char 177
    0, // char 178
    0, // char 179
    0, // char 180
    0, // char 181
    0, // char 182
    0, // char 183
    0, // char 184
    0, // char 185
    0, // char 186
    0, // char 187
    0, // char 188
    0, // char 189
    0, // char 190
    0, // char 191
    0, // char 192
    0, // char 193
    0, // char 194
    0, // char 195
    0, // char 196
    0, // char 197
    0, // char 198
    0, // char 199
    0, // char 200
    0, // char 201
    0, // char 202
    0, // char 203
    0, // char 204
    0, // char 205
    0, // char 206
    0, // char 207
    0, // char 208
    0, // char 209
    0, // char 210
    0, // char 211
    0, // char 212
    0, // char 213
    0, // char 214
    0, // char 215
    0, // char 216
    0, // char 217
    0, // char 218
    0, // char 219
    0, // char 220
    0, // char 221
    0, // char 222
    0, // char 223
    0, // char 224
    0, // char 225
    0, // char 226
    0, // char 227
    0, // char 228
    0, // char 229
    0, // char 230
    0, // char 231
    0, // char 232
    0, // char 233
    0, // char 234
    0, // char 235
    0, // char 236
    0, // char 237
    0, // char 238
    0, // char 239
    0, // char 240
    0, // char 241
    0, // char 242
    0, // char 243
    0, // char 244
    0, // char 245
    0, // char 246
    0, // char 247
    0, // char 248
    0, // char 249
    0, // char 250
    0, // char 251
    0, // char 252
    0, // char 253
    0, // char 254
    0, // char 255
};

const MD_MAX72XX::fontType_t threeBySeven[] PROGMEM = {
    0, // char 0
    0, // char 1
    0, // char 2
    0, // char 3
    0, // char 4
    0, // char 5
    0, // char 6
    0, // char 7
    0, // char 8
    0, // char 9
    0, // char 10
    0, // char 11
    0, // char 12
    0, // char 13
    0, // char 14
    0, // char 15
    0, // char 16
    0, // char 17
    0, // char 18
    0, // char 19
    0, // char 20
    0, // char 21
    0, // char 22
    0, // char 23
    0, // char 24
    0, // char 25
    0, // char 26
    0, // char 27
    0, // char 28
    0, // char 29
    0, // char 30
    0, // char 31
    3, 0x0, 0x0, 0x0, // char 32 - " "
    3, 0x0, 0xbe, 0x0, // char 33 - "!"
    3, 0x0, 0x6, 0x0, // char 34 - """
    3, 0xfe, 0x28, 0xfe, // char 35 - "#"
    3, 0x5c, 0xd6, 0x74, // char 36 - "$"
    3, 0xc4, 0x30, 0x8c, // char 37 - "%"
    3, 0x74, 0x8a, 0x94, // char 38 - "&"
    3, 0x0, 0x6, 0x0, // char 39 - "'"
    3, 0x0, 0x7c, 0x82, // char 40 - "("
    3, 0x82, 0x7c, 0x0, // char 41 - ")"
    3, 0x28, 0x10, 0x28, // char 42 - "*"
    3, 0x10, 0x38, 0x10, // char 43 - "+"
    3, 0x0, 0x80, 0x40, // char 44 - ","
    3, 0x10, 0x10, 0x10, // char 45 - "-"
    3, 0x0, 0x40, 0x0, // char 46 - "."
    3, 0xc0, 0x30, 0xc, // char 47 - "/"
    3, 0xfe, 0x82, 0xfe, // char 48 - "0"
    3, 0x84, 0xfe, 0x80, // char 49 - "1"
    3, 0xf2, 0x92, 0x9e, // char 50 - "2"
    3, 0x82, 0x92, 0xfe, // char 51 - "3"
    3, 0x1e, 0x10, 0xfe, // char 52 - "4"
    3, 0x9e, 0x92, 0xf2, // char 53 - "5"
    3, 0xfe, 0x92, 0xf2, // char 54 - "6"
    3, 0x2, 0xe2, 0x1e, // char 55 - "7"
    3, 0xfe, 0x92, 0xfe, // char 56 - "8"
    3, 0x9e, 0x92, 0xfe, // char 57 - "9"
    3, 0x0, 0x28, 0x0, // char 58 - ":"
    3, 0x80, 0x50, 0x0, // char 59 - ";"
    3, 0x10, 0x28, 0x44, // char 60 - "<"
    3, 0x28, 0x28, 0x28, // char 61 - "="
    3, 0x44, 0x28, 0x10, // char 62 - ">"
    3, 0x4, 0xb2, 0x1c, // char 63 - "?"
    3, 0x7c, 0x92, 0x5c, // char 64 - "@"
    3, 0xfc, 0x22, 0xfc, // char 65 - "A"
    3, 0xfe, 0x92, 0x6c, // char 66 - "B"
    3, 0x7c, 0x82, 0x44, // char 67 - "C"
    3, 0xfe, 0x82, 0x7c, // char 68 - "D"
    3, 0xfe, 0x92, 0x82, // char 69 - "E"
    3, 0xfe, 0x12, 0x2, // char 70 - "F"
    3, 0x7c, 0x82, 0xe4, // char 71 - "G"
    3, 0xfe, 0x10, 0xfe, // char 72 - "H"
    3, 0x82, 0xfe, 0x82, // char 73 - "I"
    3, 0x42, 0x82, 0x7e, // char 74 - "J"
    3, 0xfe, 0x10, 0xee, // char 75 - "K"
    3, 0xfe, 0x80, 0x80, // char 76 - "L"
    3, 0xfe, 0x4, 0xfe, // char 77 - "M"
    3, 0xfe, 0x2, 0xfc, // char 78 - "N"
    3, 0x7c, 0x82, 0x7c, // char 79 - "O"
    3, 0xfe, 0x22, 0x1c, // char 80 - "P"
    3, 0x7c, 0xc2, 0xbc, // char 81 - "Q"
    3, 0xfe, 0x22, 0xdc, // char 82 - "R"
    3, 0x8c, 0x92, 0x62, // char 83 - "S"
    3, 0x2, 0xfe, 0x2, // char 84 - "T"
    3, 0x7e, 0x80, 0x7e, // char 85 - "U"
    3, 0xfe, 0x40, 0x3e, // char 86 - "V"
    3, 0xfe, 0x40, 0xfe, // char 87 - "W"
    3, 0xee, 0x10, 0xee, // char 88 - "X"
    3, 0x1e, 0xe0, 0x1e, // char 89 - "Y"
    3, 0xe2, 0x92, 0x8e, // char 90 - "Z"
    3, 0x0, 0xfe, 0x82, // char 91 - "["
    3, 0xc, 0x30, 0xc0, // char 92 - "\"
    3, 0x82, 0xfe, 0x0, // char 93 - "]"
    3, 0x4, 0x2, 0x4, // char 94 - "^"
    3, 0x80, 0x80, 0x80, // char 95 - "_"
    3, 0x2, 0x4, 0x0, // char 96 - "`"
    3, 0x40, 0xa8, 0xf0, // char 97 - "a"
    3, 0xfc, 0xa0, 0x40, // char 98 - "b"
    3, 0x70, 0x88, 0x50, // char 99 - "c"
    3, 0x40, 0xa0, 0xfc, // char 100 - "d"
    3, 0x70, 0xa8, 0xb0, // char 101 - "e"
    3, 0xf8, 0x24, 0x4, // char 102 - "f"
    3, 0x90, 0xa8, 0x70, // char 103 - "g"
    3, 0xfc, 0x20, 0xc0, // char 104 - "h"
    3, 0xa0, 0xe8, 0x80, // char 105 - "i"
    3, 0x40, 0x80, 0x74, // char 106 - "j"
    3, 0xf8, 0x20, 0xd8, // char 107 - "k"
    3, 0x84, 0xfc, 0x80, // char 108 - "l"
    3, 0xf8, 0x10, 0xf8, // char 109 - "m"
    3, 0xf8, 0x8, 0xf0, // char 110 - "n"
    3, 0x70, 0x88, 0x70, // char 111 - "o"
    3, 0xf8, 0x28, 0x10, // char 112 - "p"
    3, 0x10, 0x28, 0xf8, // char 113 - "q"
    3, 0xf8, 0x8, 0x10, // char 114 - "r"
    3, 0x10, 0xa8, 0x40, // char 115 - "s"
    3, 0x7c, 0x88, 0x80, // char 116 - "t"
    3, 0x78, 0x80, 0x78, // char 117 - "u"
    3, 0xf8, 0x40, 0x38, // char 118 - "v"
    3, 0xf8, 0x40, 0xf8, // char 119 - "w"
    3, 0xd8, 0x20, 0xd8, // char 120 - "x"
    3, 0x98, 0xa0, 0x78, // char 121 - "y"
    3, 0xc8, 0xa8, 0x98, // char 122 - "z"
    3, 0x10, 0xee, 0x82, // char 123 - "{"
    3, 0x0, 0xfe, 0x0, // char 124 - "|"
    3, 0x82, 0xee, 0x10, // char 125 - "}"
    3, 0x2, 0x4, 0x2, // char 126 - "~"
    3, 0x4, 0xa, 0x4, // char 127 - ""
    0, // char 128
    0, // char 129
    0, // char 130
    0, // char 131
    0, // char 132
    0, // char 133
    0, // char 134
    0, // char 135
    0, // char 136
    0, // char 137
    0, // char 138
    0, // char 139
    0, // char 140
    0, // char 141
    0, // char 142
    0, // char 143
    0, // char 144
    0, // char 145
    0, // char 146
    0, // char 147
    0, // char 148
    0, // char 149
    0, // char 150
    0, // char 151
    0, // char 152
    0, // char 153
    0, // char 154
    0, // char 155
    0, // char 156
    0, // char 157
    0, // char 158
    0, // char 159
    0, // char 160
    0, // char 161
    0, // char 162
    0, // char 163
    0, // char 164
    0, // char 165
    0, // char 166
    0, // char 167
    0, // char 168
    0, // char 169
    0, // char 170
    0, // char 171
    0, // char 172
    0, // char 173
    0, // char 174
    0, // char 175
    0, // char 176
    0, // char 177
    0, // char 178
    0, // char 179
    0, // char 180
    0, // char 181
    0, // char 182
    0, // char 183
    0, // char 184
    0, // char 185
    0, // char 186
    0, // char 187
    0, // char 188
    0, // char 189
    0, // char 190
    0, // char 191
    0, // char 192
    0, // char 193
    0, // char 194
    0, // char 195
    0, // char 196
    0, // char 197
    0, // char 198
    0, // char 199
    0, // char 200
    0, // char 201
    0, // char 202
    0, // char 203
    0, // char 204
    0, // char 205
    0, // char 206
    0, // char 207
    0, // char 208
    0, // char 209
    0, // char 210
    0, // char 211
    0, // char 212
    0, // char 213
    0, // char 214
    0, // char 215
    0, // char 216
    0, // char 217
    0, // char 218
    0, // char 219
    0, // char 220
    0, // char 221
    0, // char 222
    0, // char 223
    0, // char 224
    0, // char 225
    0, // char 226
    0, // char 227
    0, // char 228
    0, // char 229
    0, // char 230
    0, // char 231
    0, // char 232
    0, // char 233
    0, // char 234
    0, // char 235
    0, // char 236
    0, // char 237
    0, // char 238
    0, // char 239
    0, // char 240
    0, // char 241
    0, // char 242
    0, // char 243
    0, // char 244
    0, // char 245
    0, // char 246
    0, // char 247
    0, // char 248
    0, // char 249
    0, // char 250
    0, // char 251
    0, // char 252
    0, // char 253
    0, // char 254
    0, // char 255
};
