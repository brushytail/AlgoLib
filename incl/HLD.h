#pragma once
#include "RootedTree.h"

template<class T>
struct HLD: public RootedTree<T>{
	HLD(){}
	HLD(const Arr<pair<int,T>>& pi): RT(pi), cn(n), top(n){
		int ccn=0;
		dfs_hld(r, ccn);
		ord=RT::pre();
		top[0]=r;
	}

	int lca(int a, int b){
		while(cn[a]!=cn[b]){
			if(dpt[top[cn[a]]]<dpt[top[cn[b]]]) b=p[top[cn[b]]].fi;
			else a=p[top[cn[a]]].fi;
		}
		return dpt[a]<dpt[b]?a:b;
	}

	void dfs_hld(int x, int& ccn){
		if(sz(ch[x]))
			swap(ch[x].front(), *max_element(all(ch[x]),[this](auto a, auto b){return this->tsz[a.fi]<this->tsz[b.fi];}));
		cn[x]=ccn;
		rep(i,sz(ch[x])){
			if(i)
				top[++ccn]=ch[x][i].fi;
			dfs_hld(ch[x][i].fi, ccn);
		}
	}

	void iter(int a, int b, const Func<void(int,int)>& f, bool vtxw){
		while(cn[a]!=cn[b]){
			if(dpt[top[cn[a]]]<dpt[top[cn[b]]])
				f(ord[top[cn[b]]],ord[b]+1), b=p[top[cn[b]]].fi;
			else
				f(ord[top[cn[a]]],ord[a]+1), a=p[top[cn[a]]].fi;
		}
		if(dpt[a]>dpt[b]) swap(a,b);
		f(ord[a],ord[b]+vtxw);
	}
	
	Arr<int> cn,top,ord;//chain number, top of the chain, vtx to preord
	using RT=RootedTree<T>; using RT::n; using RT::r; using RT::p; using RT::ch; using RT::dpt;
};

//See Also: https://codeforces.com/group/q4aFsZ9De9/contest/288125/submission/99012892
