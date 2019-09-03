size_t position = 0;
		while(position != string::npos)
		{
			position = _htmlPage->find("@time@", position);
			if(position != string::npos)
			{
				_htmlPage->replace(position, SIZEOFTIME,  curtime);
				position += SIZEOFTIME;
			}
		}



size_t position = 0;
		while(position != string::npos)
		{
			position = _htmlPage->find("@date@", position);
			if(position != string::npos)
			{
				_htmlPage->replace(position, SIZEOFDATE,  curdate);
				position += SIZEOFDATE;
			}
		}