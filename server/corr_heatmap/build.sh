CSRCDIR=src
JSRCDIR=out
TOOLDIR=tool
HTMLDIR=html

FILES="corr_heatmap"

mkdir -p $JSRCDIR

for i in $FILES; do
echo $i
g++ -o $JSRCDIR/$i.js -DJAVASCRIPT -E -C -P $CSRCDIR/$i.cpp
done

cp -f $HTMLDIR/main.html $JSRCDIR/.
cp -f $HTMLDIR/jquery*.js $JSRCDIR/.
cp -f $HTMLDIR/chart*.js $JSRCDIR/.


echo ------------------------------
echo Build OK!!!!!!!!
echo ------------------------------

