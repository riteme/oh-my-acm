/**
 * title: 欧拉路径(倒序输出栈里的东西)
 * category: 图论
 * description: /dev/null
 */
 
def work(u):
	global e,top
	i=head[u]
	while i>0:
#		print(str(i)+str(e[i].next))
		if e[i].c==0:
			i=e[i].next
			continue
		v=e[i].to
		e[i].c=e[i^1].c=0
		work(v)
		i=e[i].next
	st.append(u)
	top+=1
