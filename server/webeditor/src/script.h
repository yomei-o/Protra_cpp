var script="# MA Cross.pt -- 10/40移動平均交差システム by Richard Donchian\n# Copyright 2013 panacoran <panacoran@users.sourceforge.jp>\n# This program is licensed under the GPL version 3 or later.\n#\n# MA(10)がMA(40)を上抜いたらentry、下抜いたらexit。-10%の逆指値でexit。\n# ただし、終値50円以下、出来高1000万円以下の場合はentryしない。\n# 価格は翌日の寄り付きか当日の終値。買い数量は約100万円。\n\nrequire \"TIlib\"\n\ndef Num(price)\n	unit = Unit2(price)\n	return (1000000 / (unit * price)) * unit\nend\n\nif !$__INIT__\n	# TIlibのオブジェクトを生成する。\n	$MA_fast = MA_new(10)\n	$MA_slow = MA_new(40)\n	$Cross = Crossover_new(0, 0.0)\n	$__INIT__ = 1\nelse\n	MA_next($MA_fast)\n	MA_next($MA_slow)\nend\n\nma_fast = MA_value($MA_fast)\nma_slow = MA_value($MA_slow)\nprice = {+1}Open\nif !price\n	price = Close\nend\n\nif ma_fast == null || ma_slow == null || !price\n	# 指標の計算に必要な日数を経過していない場合は何もしない。\n	return\nend\ncross = Crossover_next($Cross, ma_fast, ma_slow)\n# entryの条件を判定する。\nif !$long && cross > 0 && Close > 50 && Volume * Close > 10000\n	$long = Num(price)\n	if $long == 0\n		# 100万円で買えないなら何もしない。\n		return\n	end\n	Buy(price, $long)\n	$loss_cut = Yobine(price * 0.90)\nelsif $long\n	if Low && Low <= $loss_cut\n		# 逆指値でexitする。\n		Sell(Min($loss_cut, Open), $long)\n		$long = 0\n	elsif cross < 0\n		# exitする。\n		Sell(price, $long)\n		$long = 0\n	end\nend\n\n# Local Variables:\n# tab-width: 4\n# End:\n";

