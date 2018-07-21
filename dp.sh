while true; do
./gen > data
./a <data >1.out
./b <data >2.out
if diff 1.out 2.out; then
echo AC
else
echo WA
exit 0
fi
done
