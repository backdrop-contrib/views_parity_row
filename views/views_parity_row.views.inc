<?php

/**
 * Implements hook_views_plugins().
 */
function views_parity_row_views_plugins() {
  $plugins = array('row' => array());

  $plugins['row']['views_parity_row'] = array(
    'title' => t('Content (alternate)'),
    'help' => t('Display the content with standard node view and alternate view mode according to the row index.'),
    'handler' => 'views_parity_row_plugin_row_node_parity_view',
    'path' => drupal_get_path('module', 'views_parity_row') . '/views',
    'base' => array('node'),
    'uses options' => TRUE,
    'type' => 'normal',
    'help topic' => 'style-node',
  );

  if (module_exists('entity')) {
    $entities = entity_get_info();
    foreach($entities as $entity => $entity_info) {
      $plugins['row']['views_parity_row_' . $entity_info['base table']] = array(
        'title' => t('Rendered entity (alternate)'),
        'help' => t('Display the entity with standard entity view and alternate view mode according to the row index.'),
        'handler' => 'views_parity_row_plugin_row_entity_parity_view',
        'path' => drupal_get_path('module', 'views_parity_row') . '/views',
        'base' => array($entity_info['base table']),
        'field' => array($entity_info['entity keys']['id']),
        'entity' => $entity,
        'uses options' => TRUE,
        'type' => 'normal',
      );
    }
  }

  return $plugins;
}

