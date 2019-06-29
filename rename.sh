s=1

for i in input/messages/*/*/message_1.html; do
	echo $i
	mv "$i" "input/$s.html"
	s=$((s+1))
done

echo $s