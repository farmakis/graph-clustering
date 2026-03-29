import unittest
import open3d as o3d
import numpy as np
from matplotlib import pyplot as plt

import pygcl # This is the name of the Python module created by pybind11, matching the name in CMakeLists.txt

class TestBindings(unittest.TestCase):
    def test_wcc(self):
        num_nodes = 5
        edges = [0, 1, 1, 2, 3, 4]
        expected_result = [0, 0, 0, 1, 1]  # Assuming nodes 0,1,2 are in one component and 3,4 are in separate components
        result = pygcl.connected_components(num_nodes, edges)
        print("WCC Result:", result)
        self.assertIsInstance(result, list)
        self.assertEqual(result, expected_result)

        pcd = o3d.io.read_point_cloud("tests/test.pcd")
        kd_tree = o3d.geometry.KDTreeFlann(pcd)

        num_nodes = len(pcd.points)
        edge_pairs = []
        for i in range(num_nodes):
            [_, idx, _] = kd_tree.search_knn_vector_3d(pcd.points[i], 5)
            for j in idx:
                if i != j:
                    edge_pairs.extend([i, j])

        edges = np.array(edge_pairs).flatten().tolist()
        labels = pygcl.connected_components(num_nodes, edges)

        max_label = np.asarray(labels).max()
        print(f"Number of clusters: {max_label + 1}")

        colors = plt.get_cmap("tab20")(labels / (max_label + 1))
        pcd.colors = o3d.utility.Vector3dVector(colors[:, :3])
        o3d.io.write_point_cloud("tests/test_clustered.pcd", pcd)


    # def test_dbscan(self):
    #     num_nodes = 5
    #     edges = [0, 1, 1, 2, 3, 4]
    #     eps = 0.5
    #     min_points = 2
    #     result = pygc.dbscan(num_nodes, edges, eps, min_points)
    #     self.assertIsInstance(result, list)
    #     self.assertEqual(len(result), num_nodes)

if __name__ == "__main__":
    unittest.main()