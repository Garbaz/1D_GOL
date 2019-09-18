init=""
if [ "$#" -eq "0" ];then
1>&2 printf "Usage:\ntriangle.sh NUM [STEPS]\n"
exit 1
fi
for i in `seq 1 $1`;do
	init="0$init"
done
init="1$init"
for i in `seq 1 $1`;do
	init="0$init"
done
printf "$init\n"
./1Dgol $init $2 | sed 's/0/ /g'
