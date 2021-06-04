# c) Reemplazo los "." por ".\n" y la salida la paso como entrada a sed, para eliminar las líneas vacías.
sed 's/\./\.\n/g' breve_historia.txt | sed '/^\s*$/d' > breve_historia_2.txt

# d) Primero separo las oraciones en líneas. En el resultado busco "guerra".
sed 's/\./\.\n/g' breve_historia.txt | grep -i 'guerra\b'

# e)
sed 's/\./\.\n/g' breve_historia.txt | egrep '^A.*s\.?$'

# f)
sed 's/\./\.\n/g' breve_historia.txt | grep -c 'peronismo'

# g)
sed 's/\./\.\n/g' breve_historia.txt | grep -c 'Sarmiento\b.*Rosas\b\|Rosas\b.*Sarmiento\b'

# h)
sed 's/\./\.\n/g' breve_historia.txt | egrep '18[0-9]{2}\b|XIX'

# i) Incluyo en sed las vocales con tílde para que contemple todas las palabras.
sed 's/^[a-zA-Zá-ú]*\b//g' breve_historia.txt

# j)
ls | grep '.*\.txt' 