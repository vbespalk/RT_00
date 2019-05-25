
#include "libpnt.h"

void		ft_3_inv_trans_mat(
				t_matrix *rm, t_vector transl, t_vector rot, float sc)
{
	if (!rm)
		return ;
	ft_3_identity(rm);
	if (sc != FLT_MIN)
		ft_3_matrix_scale(rm, sc, 1);
	if (!(ft_3_isnullpoint(rot)))
		ft_3_matrix_rotate(rm, rot, 1);
	if (!(ft_3_isnullpoint(transl)))
		ft_3_matrix_move(rm, transl, 1);
}
