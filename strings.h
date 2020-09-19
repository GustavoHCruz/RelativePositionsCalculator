int input(char str[], int size){
	int i=0;
	char c=getchar();

	while(c != '\n'){
		if(size > 0){
			str[i]=c;
			i++;
			size--;
		}
		c=getchar();
	}
	str[i]='\0';
	return i;
}