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

//Ajout d'une commande pour effectuer la conversion dans l'image docker ?

$commandeDocker = 'docker run -v  -ti :/data image_docker_convert_html_to_pdf input.html output.pdf'; // Commande à effectuer dans le terminal
$output = shell_exec($commandDocker); // Cette ligne effectue la commande dans php

//Boucle de vérification de conversion 

if ( $output === nul){ 
    echo 'La conversion est terminée';
} else {
    echo 'La conversion a echouée';
}
?>


