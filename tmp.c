// 42 HEADER

#include "minishell.h"

t_env *env = NULL;

int		main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)envp;
	(void)av;
	char *input;
	t_list *list;

	init_env();

	prompt();
	get_next_line(0, &input);

	list = input_to_token_list(input, NULL);

	t_token *token = list->content;
	get_abs_value(token->args);

	ft_print_token_list(list);

	free(input);
	ft_lstclear(&list, (void*)ft_token_free);
	free_all_env();
	return (0);
}
