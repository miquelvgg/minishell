//Se salta los comentarios y devuelve el string de post comentario.
char	*comentjump(char *str)
{
	while (str != 0 || *str != '\n')
		str++;
	return (str);
}
