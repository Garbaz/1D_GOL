if [ "$#" -lt "1" ];then
	1>&2 printf "Usage:\nttest.sh MAXNUM\n"
	exit 1
fi

for i in `seq 1 $1`;do
	printf "~~~$i~~~\n"
	./triangles.sh $i 100
done
