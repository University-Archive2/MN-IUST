command=$1

echo "Running $command"

if [ $command = "encode" ]
then
    ./app encode
elif [ $command = "decode" ]
then
    ./app decode
else
    echo "Invalid command"
fi