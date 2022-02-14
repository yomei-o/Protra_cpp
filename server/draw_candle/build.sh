CSRCDIR=src
JSRCDIR=out
TOOLDIR=tool
HTMLDIR=html

FILES="draw_candle"

mkdir -p $JSRCDIR

for i in $FILES; do
echo $i
g++ -o $JSRCDIR/$i.js -DJAVASCRIPT -E -C -P $CSRCDIR/$i.cpp
done

cp -f $HTMLDIR/main.html $JSRCDIR/.
cp -f $HTMLDIR/jquery*.js $JSRCDIR/.
cp -f $HTMLDIR/chart*.js $JSRCDIR/.
cp -f $HTMLDIR/lu*.js $JSRCDIR/.


echo ------------------------------
echo Build OK!!!!!!!!
echo ------------------------------

