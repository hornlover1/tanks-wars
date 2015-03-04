bool overlaps(MovableObject obj) {
	vector<QPoint> corners(obj.topLeft(), obj.TopRight(),...
	for (object obj2 in world) {
		for (QPoint pt: corners) {
			if (obj2.getGeometry().contains(pt) {
				return true;
			}
		}
	}
	return false;
}