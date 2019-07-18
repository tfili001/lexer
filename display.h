
void display_var(const var &v)
{
	cout<<"Variable ("<<v.identifier<<")\n";
		cout<<"  "<<token_to_string(v.token)<<endl;
	//cout<<"type = "<<v.type<<endl
	//cout<<"string text = "<<v.str_text<<endl
	cout<<"  value = "<<v.value<<endl
	<<"  expression [ ";
	
	for (const token_t &token : v.expression)
		cout<<token.text<<" ";
	
	cout<<"]\n";
}

void display_var_list(const vector<var> &var_list)
{
	for (const var &v : var_list)
	{
		display_var(v);
	}
}

void display_frame(const frame &f)
{
	cout<<"fn name = "<<f.fn_name<<endl
		<<"arg size = "<<f.arg_size<<endl
		<<"local vars : "<<endl;
	display_var_list(f.local_vars);
	cout<<"output stack : "<<endl;
	display_var_list(f.output_stack);
}
