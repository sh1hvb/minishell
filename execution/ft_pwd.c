
#include "../minishell.h"


void ft_pwd(t_data *data) {
    (void)data;

    size_t size = 100;
    char *buf = ft_malloc(size, 0);

    if (!buf) {
        perror("ft_malloc");
        return;
    }
    while (!getcwd(buf, size)) {
        size *= 2;
        char *new_buf = ft_malloc(sizeof(buf), 0);
        buf = new_buf;
    }
    printf("%s\n", buf);
}

