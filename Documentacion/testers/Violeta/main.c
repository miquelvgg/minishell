int main(int argc, char **argv, char **env)
{
//	t_data	data;

	(void)env;
//	ft_memset(&data, 0, sizeof(t_data));
//	if (!check_execution(&data, argc, argv))
//		exit_shelly();
//	if (data.is_interactive)
		exect_interactive(&data);
//	else
//		exect_noninteractive(&data, argc, argv);//temporal, hasta que rellenemos el data en checkexecution
//	exit_shelly(&data);
	return (0);
}
