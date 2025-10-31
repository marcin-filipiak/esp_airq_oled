<?php
$stations = $AirQ->list_station();
?>
<!DOCTYPE html>
<html lang="pl">
<head>
<meta charset="UTF-8">
<title>Przypisz flagmana do stacji</title>
<link rel="stylesheet" href="<?= MODULE_PATH ?>/assets/style.css?v=<?= time() ?>">
</head>
<body>
<div class="container">
    <h1>Przypisz flagmana</h1>

    <?php if (!empty($message)): ?>
        <div class="msg"><?= htmlspecialchars($message) ?></div>
    <?php endif; ?>

    <form method="post">
        <label for="flagman">Nazwa flagmana:</label>
        <div class="input-icon">
            <input type="text" name="flagman" id="flagman" placeholder="np. FLAG1234" required>
        </div>

        <label for="station">Wybierz stację:</label>
        <select name="station" id="station" required>
            <option value="">-- wybierz stację --</option>
            <?php if ($stations) foreach ($stations as $st): ?>
                <option value="<?= $st['id_station'] ?>"><?= htmlspecialchars($st['name']) ?></option>
            <?php endforeach; ?>
        </select>

        <button type="submit">Zapisz</button>
    </form>
</div>
</body>
</html>

