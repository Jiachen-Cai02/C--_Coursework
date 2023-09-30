echo "echo Restoring environment" > "/workspaces/PHAS0100Assignment2/build/deactivate_conanrunenv-release-armv8.sh"
for v in 
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "/workspaces/PHAS0100Assignment2/build/deactivate_conanrunenv-release-armv8.sh"
    else
        echo unset $v >> "/workspaces/PHAS0100Assignment2/build/deactivate_conanrunenv-release-armv8.sh"
    fi
done

