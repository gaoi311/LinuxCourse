MYDATE=`date +%d/%m/%y`
THIS_HOST=`hostname -s`
USER=`whoami`

file_run()
{
echo "you must complete it"
}
uers()
{
echo "there are `who|wc -l` users online"
echo -e "who are\n`who|awk '{print $1}'`" 
}

while :
do
	tput clear
	cat <<aaa
---------------------------------------------------------------------
User:$USER		Host:$THIS_HOST			Date:$MYDATE
---------------------------------------------------------------------
		1 : List subdirectory in current directory 
		2 : List files in current directory which can run
		3 : See who is on the system
		H : Help screen
		Q : Exit Menu
--------------------------------------------------------------------
aaa
	echo -e -n "\tYour Choice [1,2,3,H,Q] >"
	read CHOICE
	case $CHOICE in
	1) ls -l|awk '/^d/ {print $8}' 
	;;
	2) file_run 
	;;
	3) uers
	;;
	H|h)
	cat <<aaa
This is the help screen,nothing here yet to help you!
aaa
;;
	Q|q) exit 0
	;;
	*) echo -e "\t\007 unkown user response"
	;;
	esac
	echo -e -n "\n\n\tHit the return key to continue"
	read DUMMY
done
