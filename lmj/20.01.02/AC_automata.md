```
void build () {
	int i , k;
	queue < int > que;
	ord[++index] = 0;
	for ( i = 1 ; i <= 27 ; i++ ) {
		if ( p[0].ch[i] ) {
			que.push ( p[0].ch[i] );
			ord[++index] = p[0].ch[i];
		}
	}
	while ( que.size() ) {
		k = que.front (); que.pop ();
		ord[++index] = k;
		for ( i = 1 ; i <= 27 ; i++ ) {
			if ( p[k].ch[i] ) {
				p[p[k].ch[i]].fail = p[p[k].fail].ch[i];
				que.push ( p[k].ch[i] ); 
			}
			else {
				p[k].ch[i] = p[p[k].fail].ch[i];
			}
		}
	}
}
```

