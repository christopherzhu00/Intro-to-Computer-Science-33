//Christopher Zhu
//UID: 104455996
// 3.59



int switch_prob(int x, int n)
{
	int result = x;
	switch(n)
	{
		case 50:
		case 52:
			result = result << 2;
			break;
		case 53:
			result = result >> 2;
			break;
		case 54:
			result = (result * 3)
			break;
		case 55:
			result = (result * result);
			break;
		default:
			result += 10;
			break;
	}
	return result;
}