using Sqlite;

static const string query = "INSERT INTO score (login, level, time) VALUES (?, ?, strftime('%s', 'now()'));";

int main(string[] args) {
	Database db;
	Statement st;
	int rc, egid = 0;
	string login = Environment.get_user_name();

	if((rc = Database.open("/srv/score.db", out db)) != OK) {
		stderr.printf("Can't open database: %s\n", db.errmsg());
		return 1;
	}

	egid = (int)Posix.getegid();
	if(!(1000 < egid < 1006)) {
		stderr.printf("Execute this script only with gained group rights\n");
		return 1;
	}

	db.prepare(query, (int)query.length, out st, null);
	st.bind_text(1, login);
	st.bind_int(2, egid - 1000 + 1);

	if((rc = st.step()) != DONE) {
		stderr.printf("You already submitted the level\n");
		return 1;
	}

	try {
		Process.spawn_command_line_sync("/usr/sbin/usermod %d %s".printf(egid, login));
	}
	catch(SpawnError e) {
		error(e.message);
	}

	return 0;
}

