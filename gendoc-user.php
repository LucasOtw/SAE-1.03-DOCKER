<?php // Création du fichier html de manière dynamique
$htmlContent = "<html> 
<head>
    <title>SAE1.03-Docker</title></head>
    <body>
        <h1>Test pour la conversion de fichier html => PDF</h1>
            <p>CE texte est un exemple pour le test</p>
    </body>
</html>";
$htmlFile = 'doc-tech-<0.1>.html'; // Enregistrement et renomage du fichier
file_put_contents($htmlFile, $htmlContent); // Enregistrement du contenu de htmlContent dans une variable (htmlFile)
?>


