for(( i = 1; i <= 20; i++ )); do
    touch ./resultado/$i.out
    ./main.exe < ../casos_teste/$i.in > ./resultado/$i.out
done